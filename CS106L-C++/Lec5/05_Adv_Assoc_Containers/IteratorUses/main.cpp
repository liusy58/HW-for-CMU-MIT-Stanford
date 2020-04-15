#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

using std::string;  using std::cin;
using std::cout;    using std::endl;
using std::vector;     using std::stringstream;
using std::set;


int main() {
    vector<int> vec{3,1,4,1,5,9,2,6,5,3};

    // we can use iterators in algorithms like sort to sort a vecotr
    std::sort(vec.begin(), vec.end());


    // we can also use the find algorithm to look for an element
    // in a collection and return an iterator to it
    vector<int>::iterator it = std::find(vec.begin(), vec.end(), 5);
    if(it != vec.end()) {
       cout << "Found elem " << *it << endl;
    } else {
       cout << "Element not found " << endl;
    }



    set<int> mySet{4,1,3,5,55,5, 9, 22, 19, 28};

    // we can iterate through a range of elements in
    // a sorted collection
    set<int>::iterator iter = mySet.lower_bound(7);
    set<int>::iterator end = mySet.upper_bound(28);

    while(iter != end) {
        cout << *iter << endl;
        ++iter;
    }

    return 0;
}
