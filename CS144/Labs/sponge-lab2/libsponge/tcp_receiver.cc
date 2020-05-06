#include "tcp_receiver.hh"

// Dummy implementation of a TCP receiver

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

bool TCPReceiver::segment_received(const TCPSegment &seg) {
    //Set the Initial Sequence Number if necessary.
    TCPHeader seg_head=seg.header();
    if(!_connected&&!seg_head.syn)
        return false;
    if(!_connected&&seg_head.syn)
    {
        _connected=1;
        _isn=seg_head.seqno;
        _ackno=seg_head.seqno;
    }

    size_t seg_data_len=seg.length_in_sequence_space();
    //A segment is acceptable (and the method should return true) if any of the sequence numbers it occupies falls inside the receiver’s window.
    

    if(can_contain(seg_data_len,seg_head.seqno))
    {
        size_t seqno_unwrapped=unwrap(seg_head.seqno,_isn,_reassembler.stream_out().bytes_written())-1;

        _reassembler.push_substring(seg.payload().copy(),seqno_unwrapped,seg_head.fin);


        if(_ackno==seg_head.seqno)
        {
            _ackno=wrap(_reassembler.first_unassembled(),_isn)+1;
            if(seg_head.fin)
                _ackno=_ackno+1;
        }
        return true;
    }
    return false;
}


//! \name Accessors to provide feedback to the remote TCPSender
//!@{

//! \brief The ackno that should be sent to the peer
//! \returns empty if no SYN has been received
//!
//! This is the beginning of the receiver's window, or in other words, the sequence number
//! of the first byte in the stream that the receiver hasn't received.
optional<WrappingInt32> TCPReceiver::ackno() const { 
    if(_connected)
        return _ackno;
    return {};
 }


size_t TCPReceiver::window_size() const { 
    return _reassembler.stream_out().remaining_capacity();
 }

bool TCPReceiver::can_contain(size_t data_len,WrappingInt32 seqno)
{
    int32_t window_left=_ackno.raw_value();
    int32_t window_right=_ackno.raw_value()+window_size()-1;

    int32_t data_left=seqno.raw_value();
    int32_t data_right=seqno.raw_value()+data_len-1;
    if((data_left>=window_left&&data_left<=window_right)||(data_right>=window_left&&data_right<=window_right))
        return true;
    return false;
}
