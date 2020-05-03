#include "GraphInternal.h"
#include <sstream>
#include <iomanip>
using namespace std;

RealColor RealColor::darker() const {
    return { 3 * r / 4, 3 * g / 4, 3 * b / 4 };
}

string RealColor::toString() const {
    ostringstream result;
    result << '#';

    result << hex << setw(2) << setfill('0') << r;
    result << hex << setw(2) << setfill('0') << g;
    result << hex << setw(2) << setfill('0') << b;

    return result.str();
}
