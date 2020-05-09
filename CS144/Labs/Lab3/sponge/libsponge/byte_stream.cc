#include "byte_stream.hh"

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <cassert> 
#include <iostream>
// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;



ByteStream::ByteStream(const size_t capacity):_capacity(capacity),_eof(0),_input_ended(0),_written_bytes(0),_read_bytes(0) {}




//! Write a string of bytes into the stream. Write as many
//! as will fit, and return how many were written.
//! \returns the number of bytes accepted into the stream

size_t ByteStream::write(const string &data) {
    size_t maximum_bytes=min(data.size(),remaining_capacity());
    
    size_t cnt=0;

    //cerr<<"in ByteStream::write  maximum_bytes: "<<maximum_bytes<<endl;
    //cerr<<"in ByteStream::write  _buffer.size():"<<buffer_size()<<endl;

    //cerr<<"in ByteStream::write push_back   ";
    for(;cnt<maximum_bytes;++cnt)
    {
        //cerr<<data[cnt];
        _buffer.push_back(data[cnt]);
    }
    ////cerr<<endl;
    _written_bytes+=cnt;
    
    ////cerr<<"in ByteStream::write  _buffer.size():"<<buffer_size()<<endl;
    return cnt;
}

//! \param[in] len bytes will be copied from the output side of the buffer


//!\note just copy not pop out
string ByteStream::peek_output(const size_t len) const {
    

    auto cnt=min(len,buffer_size());
    ////cerr<<"in ByteStream::peek_output  cnt: "<<cnt<<"len: "<<len<<"buffer_size(): "<<buffer_size()<<endl;
    if(cnt<=0)
        return "";
    
    return string(_buffer.begin(),_buffer.begin()+cnt);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    assert(len<=buffer_size());

    size_t i=0;
    for(;i<len&&!_buffer.empty();++i)
        _buffer.pop_front();
    _read_bytes+=i;
    if(input_ended()&&buffer_empty())
        _eof=1;
    
 }

//! \returns `true` if the stream input has ended
void ByteStream::end_input() {
    _input_ended=1;
    if(buffer_empty())
        _eof=1;
}



bool ByteStream::input_ended() const { 
    return _input_ended;
 }


//! \returns the maximum amount that can currently be read from the stream
size_t ByteStream::buffer_size() const { 
    return _buffer.size();
 }


//! \returns `true` if the buffer is empty
bool ByteStream::buffer_empty() const { 
    return _buffer.empty();
 }



//! \returns `true` if the output has reached the ending
bool ByteStream::eof() const { 
    return _eof;
 }

size_t ByteStream::bytes_written() const { 
    return _written_bytes;
 }

size_t ByteStream::bytes_read() const { 
    return _read_bytes;
 }

size_t ByteStream::remaining_capacity() const { 
    return _capacity-_buffer.size();
 }





/*
Some bugs:
1.error: ‘deque’ does not name a type
     deque<char>_buffer;//buffer to hold the byte
Solution: using std::deque<char>需要加上std


2. if 语句

void ByteStream::end_input() {
    _input_ended=1;
    if(buffer_empty())
        _eof=1;
}


3.
//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    assert(len<=buffer_size());

    for(size_t i=0;i<len;++i)
        _buffer.pop_back();
    _read_bytes+=len;
    if(input_ended()&&buffer_empty())
        _eof=1;
    
 }
 _buffer.pop_back();-> _buffer.pop_front();

*/

