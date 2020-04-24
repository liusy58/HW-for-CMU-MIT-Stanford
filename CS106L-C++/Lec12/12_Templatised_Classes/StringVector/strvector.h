#ifndef STRVECTOR_H
#define STRVECTOR_H

#include <string>
#include <algorithm>


class StrVector {
public:
    using iterator = std::string*;
    using size_type = size_t;

    const size_type kInitialSize = 2;
    StrVector();
    StrVector(size_type n, const std::string& val);
    ~StrVector();

    size_type size() const;
    bool empty() const;

    std::string& operator[](size_type indx);
    const std::string& operator[](size_type indx) const;
    std::string& at(size_type indx);

    iterator insert(iterator pos, const std::string& elem);
    void push_back(const std::string& elem);

    iterator begin();
    iterator end();

private:
    void grow();
    std::string* elems;
    size_type logicalSize;
    size_type allocatedSize;
};





#endif // STRVECTOR_H


