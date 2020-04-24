#include <strvector.h>


StrVector::StrVector() :
    logicalSize(0), allocatedSize(kInitialSize)
{
    elems = new std::string[allocatedSize];
}

StrVector::StrVector(size_type n, const std::string &val) :
    logicalSize(n), allocatedSize(2*n)
{
    elems = new std::string[allocatedSize];
    std::fill(begin(), end(), val);
}


StrVector::~StrVector() {
    delete[] elems;
}


StrVector::iterator StrVector::begin() {
    return elems;
}


StrVector::iterator StrVector::end() {
    return elems + size();
}


StrVector::size_type StrVector::size() const {
    return logicalSize;
}


bool StrVector::empty() const {
    return size() == 0;
}


std::string& StrVector::operator[](size_type index) {
    return *(begin() + index);
}


std::string& StrVector::at(size_type index) {
    if(index >= size()) {
        throw std::out_of_range("Out of bounds access of vector");
    }
    return *(begin() + index);
}


void StrVector::grow() {
    iterator new_elems = new std::string[2*allocatedSize];
    std::copy(begin(), end(), new_elems);
    delete[] elems;
    allocatedSize *= 2;
    elems = new_elems;
}


StrVector::iterator StrVector::insert(iterator pos, const std::string &elem) {
    size_type indx = pos - begin();
    if(size() == allocatedSize) {
        grow();
    }
    /*
      * If we grew, we need pos to point to the new array
      * since the previous address of pos would be invalid
      */
    pos = begin() + indx;
    std::copy_backward(pos, end(), end() + 1);
    *pos = elem;
    ++logicalSize;
    return pos;
}


void StrVector::push_back(const std::string &elem) {
    insert(end(), elem);
}
