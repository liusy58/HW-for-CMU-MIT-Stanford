#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout;    using std::cin;
using std::endl;    using std::string;
using std::vector;  using std::ostream;

class AddNum {
public:

    AddNum(int inp) {
        startNum = inp;
    }

    int operator()(int x) {
        return x + startNum;
    }

private:
    int startNum;
};


int main() {
    // Construct functor with initial value of 5.
    AddNum a(5);

    // Calling as function adds value originally passed
    // into constructor to paramter.
    cout << a(4) << endl;

    return 0;
}

