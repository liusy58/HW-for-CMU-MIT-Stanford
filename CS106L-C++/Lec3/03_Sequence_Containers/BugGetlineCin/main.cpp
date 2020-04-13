#include <iostream>
#include <string>

using std::cout;    using std::endl;
using std::cin;     using std::string;


int main() {
    cout << "Enter your favourite number: ";

    int favNum;
    cin >> favNum;

    cout << "Enter your full name: ";

    // Consume all possible whitespace from current
    // position in buffer.
    cin >> std::ws;         // Comment this out to see bug.

    // cin won't have a remaining new line character
    // so will wait for user input.
    string fullName;
    std::getline(cin, fullName);

    cout << "Hello, " << fullName << "!" << endl;
    cout << "Your favourite number is " << favNum << endl;

    return 0;
}
