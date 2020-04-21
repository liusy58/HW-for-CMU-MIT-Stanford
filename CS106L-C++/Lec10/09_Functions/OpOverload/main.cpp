
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout;    using std::cin;
using std::endl;    using std::string;
using std::vector;  using std::ostream;

ostream& operator<<(ostream& os, vector<int> x) {
    os << "{";
    for(auto i : x) {
        os << i << " ";
    }
    os << "}";
    return os;
}


struct Point {
    int x;
    int y;
    /*
     * Operator defined as member function is called
     * on instance of the class. So only the right
     * hand side is passed as a parameter.
     */
    bool operator==(const Point& rhs) {
        return x == rhs.x && y == rhs.y;
    }
};

/*
 * Operator defined as non-member function is defined
 * outside of class so needs to take both lhs and rhs
 * argument as parameters.
 */
bool operator<(const Point& lhs, const Point& rhs) {
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}


int main() {
    vector<int> v{3, 1, 4, 1, 5, 9};
    cout << v << endl;

    Point p1{3, 1};
    Point p2{1, 0};
    Point p3{3, 1};

    if(p1 == p3) {
        cout << "P1 and P3 are equal" << endl;
    }

    if(p2 < p1) {
        cout << "P2 less than P1" << endl;
    }
}
