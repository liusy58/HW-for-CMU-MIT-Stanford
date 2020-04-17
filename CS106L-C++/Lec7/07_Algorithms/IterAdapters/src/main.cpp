#include <iostream>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

void printVector(vector<int>& nums) {
    cout << "{";
    for (auto elem : nums) {
        cout << elem << ", ";
    }
    cout << "}" << endl;
}



int main() {
    std::ostream_iterator<int> iter(cout, ", ");
    *iter = 15;
    ++iter;
    *iter = 1;

    cout << endl;

    vector<int> vec{3,1,4,1,5,9,2,6,5,3};

    printVector(vec);

    // full type is annoying to write so we'll use auto
    // std::back_insert_iterator<vector<int>> it = std::back_inserter(vec);
    auto it = std::back_inserter(vec);

    *it = 5;
    ++it;
    *it = 12;

    printVector(vec);
}

