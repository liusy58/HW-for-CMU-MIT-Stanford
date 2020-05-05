#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity),_unassembled_bytes(0),_first_unassembled_index(0),_eof(0),index2str() {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    if(eof)
    {
        _eof=1;
    }

    //[index,index+data.size()-1]
    size_t _data_first=index;
    size_t _data_last=index+data.size()-1;
    if(_data_last<_first_unassembled_index||!data.size())
    {
        if(_eof&&empty())
            _output.end_input();
        return;
    }

    _data_first=max(_data_first,_first_unassembled_index);  
    for(auto iter=index2str.begin();iter!=index2str.end();)
    {
        size_t left=iter->first;
        size_t right=left+iter->second.size()-1;

        int relation=cal_relation(left,right,_data_first,_data_last);

        switch(relation)
        {
            case 1:
                iter++;
                break;
            case 2:
                _data_first=right+1;
                iter++;
                break;
            case 3:
                return;
            case 4:
                _unassembled_bytes-=iter->second.size();
                iter=index2str.erase(iter);
                break;
            case 5:
                _data_last=left-1;
                iter++;
                break;
            case 6:
                break;
            default:
                assert("Invalid !");
                break;
        }
        if(relation==6)
            break;
    }



    if(_data_first>_data_last)
        return;


    string str(data.begin()+_data_first-index,data.begin()+_data_last-index+1);


    index2str[_data_first]=str;

    _unassembled_bytes+=str.size();

    for(auto iter=index2str.begin();iter!=index2str.end();)
    {
        size_t left=iter->first;
        //size_t right=left+iter->second.size()-1;

        size_t len=iter->second.size();
        if(_first_unassembled_index==left)
        {
            if(_output.remaining_capacity()>=len)
            {
                _output.write(iter->second);
                _unassembled_bytes-=len;
                iter=index2str.erase(iter);
                _first_unassembled_index+=len;
                continue;
            }
            else
            {
                size_t _len=_output.remaining_capacity();

                size_t _index=_first_unassembled_index+_len;
                
                string _str(data.begin(),data.begin()+_len);
                assert(data.begin()<data.begin()+_len);

                string _str2(data.begin()+_len,data.end());
                assert(data.begin()+_len<data.end());

                _output.write(_str);
                index2str[_index]=_str2;
                iter=index2str.erase(iter);
                _unassembled_bytes-=_str.size();
                _first_unassembled_index+=_len;
                break;
            }
            
        }
        break;
    }
    if(_eof&&empty())
            _output.end_input();
}



size_t StreamReassembler::unassembled_bytes() const { 
    return _unassembled_bytes;
 }



//! \brief Is the internal state empty (other than the output stream)?
//! \returns `true` if no substrings are waiting to be assembled
bool StreamReassembler::empty() const { 
    return !_unassembled_bytes;
 }



//! left2 is the first index of the new data

int StreamReassembler::cal_relation(int left1,int right1,int left2,int right2)
{
    //1:
    if(right1<left2)
        return 1;

    //2
    if(left1<=left2&&right1<=right2)
        return 2;
    //3
    if(left1<=left2&&right1>=right2)
        return 3;
    
    if(left1>=left2&&right1<=right2)
        return 4;
    
    if(left1>=left2&&left1<=right2&&right1>right2)
        return 5;
    
    if(left1>right2)
        return 6;
    
    return 0;
}



/*
            case 4:
                ***_unassembled_bytes-=iter->second.size();
                iter=index2str.erase(iter);
                break;


*/
