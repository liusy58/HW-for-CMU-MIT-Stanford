#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <string>
#include <algorithm>

template <class ValueType>
class MyVector {

public:
    using iterator = ValueType*;
    using size_type = size_t;

    const size_type kInitialSize = 10;
    MyVector();
    MyVector(size_type n, const ValueType& val);
    ~MyVector();

    size_type size() const;
    bool empty() const;

    ValueType& operator[](size_type indx);
    ValueType& at(size_type indx);

    iterator insert(iterator pos, const ValueType& elem);
    void push_back(const ValueType& elem);

    iterator begin();
    iterator end();

private:
    void grow();
    ValueType* elems;
    size_type logicalSize;
    size_type allocatedSize;
};


template <class ValueType>
MyVector<ValueType>::MyVector() :
    logicalSize(0), allocatedSize(kInitialSize)
{
    elems = new ValueType[allocatedSize];
}

template <class ValueType>
MyVector<ValueType>::MyVector(size_type n, const ValueType &val) :
    logicalSize(n), allocatedSize(2*n)
{
    elems = new ValueType[allocatedSize];
    std::fill(begin(), end(), val);
}

template <class ValueType>
MyVector<ValueType>::~MyVector() {
    delete[] elems;
}

template <class ValueType>
auto MyVector<ValueType>::begin() -> iterator {
    return elems;
}

template <class ValueType>
typename MyVector<ValueType>::iterator MyVector<ValueType>::end() {
    return elems + size();
}

template <class ValueType>
typename MyVector<ValueType>::size_type MyVector<ValueType>::size() const {
    return logicalSize;
}

template <class ValueType>
bool MyVector<ValueType>::empty() const {
    return size() == 0;
}

template <class ValueType>
ValueType& MyVector<ValueType>::at(size_type index) {
    if(index >= size()) {
        throw std::out_of_range("Out of bounds access of vector");
    }
    return *(begin() + index);
}


template <class ValueType>
ValueType& MyVector<ValueType>::operator[](size_type index) {
    return *(begin() + index);
}

template <class ValueType>
void MyVector<ValueType>::grow() {
    iterator new_elems = new ValueType[2*allocatedSize];
    std::copy(begin(), end(), new_elems);
    delete[] elems;
    allocatedSize *= 2;
    elems = new_elems;
}

template <class ValueType>
typename MyVector<ValueType>::iterator MyVector<ValueType>::insert(iterator pos, const ValueType &elem) {
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

template <class ValueType>
void MyVector<ValueType>::push_back(const ValueType &elem) {
    insert(end(), elem);
}


#endif // MYVECTOR_H


