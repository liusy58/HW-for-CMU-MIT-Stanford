#include "wrapping_integers.hh"

// Dummy implementation of a 32-bit wrapping integer

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

//! Transform an "absolute" 64-bit sequence number (zero-indexed) into a WrappingInt32
//! \param n The input absolute 64-bit sequence number
//! \param isn The initial sequence number
WrappingInt32 wrap(uint64_t n, WrappingInt32 isn) {
//! Transform a 64-bit absolute sequence number (zero-indexed) into a 32-bit relative sequence number
//! \param n the absolute sequence number
//! \param isn the initial sequence number
//! \returns the relative sequence number
    uint64_t t=1;
    return WrappingInt32((isn.raw_value()+n)%(t<<32));
    //return WrappingInt32((isn.raw_value()+n));

}

//! Transform a WrappingInt32 into an "absolute" 64-bit sequence number (zero-indexed)
//! \param n The relative sequence number
//! \param isn The initial sequence number
//! \param checkpoint A recent absolute 64-bit sequence number
//! \returns the 64-bit sequence number that wraps to `n` and is closest to `checkpoint`
//!
//! \note Each of the two streams of the TCP connection has its own ISN. One stream
//! runs from the local TCPSender to the remote TCPReceiver and has one ISN,
//! and the other stream runs from the remote TCPSender to the local TCPReceiver and
//! has a different ISN.
uint64_t unwrap(WrappingInt32 n, WrappingInt32 isn, uint64_t checkpoint) {
    WrappingInt32 checkpoint_wrap = wrap(checkpoint,isn);
    
    //非符号数相减，小的减大的
    int32_t diff1=n-checkpoint_wrap;
    int32_t diff2=checkpoint_wrap-n;

    if(diff1>=0||checkpoint-diff2>checkpoint)
        return checkpoint+static_cast<uint32_t>(diff1);
    else
        return checkpoint-diff2;  
}
