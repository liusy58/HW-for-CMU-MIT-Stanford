#include <iostream>
#include <vector>
#include "strvector.h"

using std::cout;    using std::endl;
using std::string;

void printVec(StrVector& v) {
    for(size_t i = 0; i < v.size(); ++i)
        cout << v[i] << ", ";

    cout << endl;
}

int main() {
    StrVector v(5, "yes");
    v.push_back("hello");
    v.push_back("world");
    v.push_back("asdf");

    for(size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << endl;
    }

    /*
     * This doesn't swork because we have not specified
     * const versions of our accessor methods.
     *
     *    const Vector<string> constV(10, "iamconst");
     *    cout << constV[0] << endl;
     */
    return 0;
}
