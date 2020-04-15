#include <iostream>
#include <string>
#include <vector>
#include <set>

using std::string;  using std::cin;
using std::cout;    using std::endl;
using std::vector;  using std::set;


// vector of elements, and given element
// {3,1,4,1,5,9,2,6,5,3,12,14}, elem=10
// return = 12

// return the smallest element in the vector that
// is greater than or equal this element


// vec is already sorted
int findSupremum(const vector<int>& vec, int elem) {

    vector<int>::const_iterator it = std::upper_bound(vec.begin(), vec.end(), elem);

    if(it != vec.end()) {
        return *it;
    } else {
        return -1;
    }

}

int main() {
    vector<int> vec{3,1,4,1,5,9,2,6,5,3,12,14};
    std::sort(vec.begin(), vec.end());


    cout << findSupremum(vec, 10) << endl;


    return 0;
}
