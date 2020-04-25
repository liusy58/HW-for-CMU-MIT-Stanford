#include "byte_stream.hh"

#include <algorithm>
#include <iterator>
#include <stdexcept>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity): _stream(), _size(0), _capacity(capacity), _eof(false), _input_ended(false), _nWritten(0), _nRead(0) {}

size_t ByteStream::write(const string &data) {
    size_t remaining_capacity=_capacity-_size;
    for(size_t i=0;i<data.size()&&i<remaining_capacity;++i)
        _stream.push_back(data[i]);
    
    _size+=i;
    _nWritten+=i;
    return i;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
   
   return string(_stream.begin(),_stream.begin()+min(len, _size));
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    size_t cnt=min(len,_size);
    for(size_t i=0;i<cnt;++i)
        _stream.pop_front();
    _size-=cnt;
    _nRead+=cnt;
    if (buffer_empty() && input_ended()) // XXX 如果缓冲区读完了且写者不会再写入任何数据，则该字节流肯定就结束了。
        _eof = true;
}

void ByteStream::end_input() {
    _input_ended = true;
    if (buffer_empty())
        _eof = true;
}

bool ByteStream::input_ended() const { 
    return _input_ended; }

size_t ByteStream::buffer_size() const { 
    return _size; }

bool ByteStream::buffer_empty() const { return !_size; }

bool ByteStream::eof() const { return _eof; }

size_t ByteStream::bytes_written() const { return _nWritten; }

size_t ByteStream::bytes_read() const { return _nRead; }

size_t ByteStream::remaining_capacity() const { return _capacity-_size}; }
