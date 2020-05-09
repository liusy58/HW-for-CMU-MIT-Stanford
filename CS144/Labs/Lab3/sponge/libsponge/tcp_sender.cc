#include "tcp_sender.hh"

#include "tcp_config.hh"

#include <random>
#include <iostream>
// Dummy implementation of a TCP sender

// For Lab 3, please replace with a real implementation that passes the
// automated checks run by `make check_lab3`.

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

//! \param[in] capacity the capacity of the outgoing byte stream
//! \param[in] retx_timeout the initial amount of time to wait before retransmitting the oldest outstanding segment
//! \param[in] fixed_isn the Initial Sequence Number to use, if set (otherwise uses a random ISN)
TCPSender::TCPSender(const size_t capacity, const uint16_t retx_timeout, const std::optional<WrappingInt32> fixed_isn)
    : _isn(fixed_isn.value_or(WrappingInt32{random_device()()}))
    , _initial_retransmission_timeout{retx_timeout}
    ,_retransmissionTimeout{retx_timeout}
    , _stream(capacity)
    , _outstandingSegments() {}

uint64_t TCPSender::bytes_in_flight() const 
{
    return _nBytesInFlight;
}
//! \brief create and send segments to fill as much of the window as possible

//use the TCPSegment::length in sequence space() method to count the total number of sequence numbers occupied by a segment.
//
void TCPSender::fill_window() {
    if(_finSent)
        return;
    //建立连接阶段
    // create a TCPSegment variable 
    TCPSegment newsegment;
    TCPHeader&hdr=newsegment.header();
    if(!_next_seqno)
    {
        hdr.syn=1;
    }
    else
    {      
        // make TCPSegment as big as possible, but no bigger than the value given by TCPConfig::MAX_PAYLOAD_SIZE
        size_t size=min(TCPConfig::MAX_PAYLOAD_SIZE,_notifyWinSize);
        string data=_stream.read(size);
        //move the data to the playload
        newsegment.payload()=Buffer(move(data));
        if (_stream.input_ended() && newsegment.length_in_sequence_space()<_notifyWinSize) { // 如果接受窗口还有空间的话。
            hdr.fin = true;
            _finSent = true;
        }
    }

    //count the total number of sequence numbers occupied by a segment.
    size_t cnt=newsegment.length_in_sequence_space();

    if(cnt)
    {
        hdr.seqno=wrap(_next_seqno, _isn);
        _nBytesInFlight+=cnt;
        _next_seqno+=cnt;
        _notifyWinSize-=cnt;
        _outstandingSegments.insert(newsegment);
        _segments_out.push(newsegment);
    }




}

//! \param ackno The remote receiver's ackno (acknowledgment number)
//! \param window_size The remote receiver's advertised window size
//! \returns `false` if the ackno appears invalid (acknowledges something the TCPSender hasn't sent yet)
bool TCPSender::ack_received(const WrappingInt32 ackno, const uint16_t window_size) {


    //returns false if the ackno appears invalid,
    if(unwrap(ackno,_isn,_next_seqno)>_next_seqno)
        return false;
    _notifyWinStart=unwrap(ackno,_isn,_next_seqno);
    _notifyWinSize=window_size;

    for(auto iter=_outstandingSegments.begin();iter!=_outstandingSegments.end();)
    {
        uint64_t seg_right=unwrap(iter->header().seqno,_isn,_next_seqno)+iter->length_in_sequence_space();
        if(seg_right<=_notifyWinStart)
        {
            _nBytesInFlight-=iter->length_in_sequence_space();
            iter=_outstandingSegments.erase(iter);
        }
            
        else
            iter++;
    }
    
    while(!_segments_out.empty())
    {
        uint64_t seg_right=unwrap(_segments_out.front().header().seqno,_isn,_next_seqno)+_segments_out.front().length_in_sequence_space();
        if(seg_right<=_notifyWinStart)
            _segments_out.pop();
        else
            break;
    }
//(a) Set the RTO back to its “initial value.”
    _retransmissionTimeout=_initial_retransmission_timeout;
//(b) If the sender has any outstanding data, restart the retransmission timer so that it will expire after RTO milliseconds (for the current value of RTO).
    if(!_outstandingSegments.empty())
        _retransmissionTimer=0;
//(c) Reset the count of “consecutive retransmissions” back to zero.
    _nConsecutiveretransmissions=0;
    return true;
        
}

//! \param[in] ms_since_last_tick the number of milliseconds since the last call to this method
void TCPSender::tick(const size_t ms_since_last_tick) { 

//(b) If the window size is nonzero:
    //i. Keep track of the number of consecutive retransmissions, and increment it because you just retransmitted something. Your TCPConnection will use this information to decide if the connection is hopeless (too many consecutive retransmissions in a row) and needs to be aborted.
    //ii. Double the value of RTO. 3
//(c) Start the retransmission timer, such that it expires after RTO milliseconds (for the value of RTO after the doubling operation outlined in the previous bullet point).
    _retransmissionTimer+=ms_since_last_tick;
    if(_retransmissionTimer>=_retransmissionTimeout)
    {
        //(a) Retransmit the earliest (lowest sequence number) segment that hasn’t been fully acknowledged by the TCP receiver. You’ll need to be storing the outstanding segments in some internal data structure that makes it possible to do this.
        _segments_out.push(*_outstandingSegments.begin());
        //(b) If the window size is nonzero:
            //i. Keep track of the number of consecutive retransmissions, and increment it because you just retransmitted something. Your TCPConnection will use this information to decide if the connection is hopeless (too many consecutive retransmissions in a row) and needs to be aborted.
            //ii. Double the value of RTO. 
        if(_notifyWinSize||_next_seqno==1)
        {
            _nConsecutiveretransmissions++;
            _retransmissionTimeout*=2;
        }
        _retransmissionTimer=0;
    }
}

unsigned int TCPSender::consecutive_retransmissions() const { 
    return _nConsecutiveretransmissions; }


//This kind of segment—one that carries no data and occupies no sequence numbers—doesn’t need to be kept track of as “outstanding” and won’t ever be retransmitted.
void TCPSender::send_empty_segment() {
    TCPSegment seg;
    seg.header().seqno = wrap(_next_seqno, _isn);
    _segments_out.push(seg);
}




/*
t_send_transmit:
修改了fill_window函数里面的size_t size=min(TCPConfig::MAX_PAYLOAD_SIZE,_notifyWinSize);



if(_retransmissionTimer>=_retransmissionTimeout)的>=


    if(!_outstandingSegments.empty())
        _retransmissionTimer=0;


Retx SYN twice at the r
if(_notifyWinSize||_next_seqno==1)
        {
            _nConsecutiveretransmissions++;
            _retransmissionTimeout*=2;
        }



test--"FIN flag occupies space in window
if (_stream.input_ended() && seg.length_in_sequence_space()<_notifyWinSize) { // 如果接受窗口还有空间的话。
            hdr.fin = true;
            _finSent = true;
        }
*/