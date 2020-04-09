
#include <iostream>

using std::cout;
using std::endl;

void streamTypeTests() {
   cout << "Strings work!" << endl;
   cout << 1729 << endl;
   cout << 3.14 << endl;
   cout << "Mixed types - " << 1123 << endl;
   cout << 23*2 << endl;
}

int main() {
   streamTypeTests();
   return 0;
}
