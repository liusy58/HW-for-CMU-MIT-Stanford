
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::string;

void writeToStream(std::ostream& anyOutputStream, int favouriteNumber) {
    anyOutputStream << "Writing to stream: "
        << favouriteNumber << endl;
}

int main() {
    // Write an int to the user's console.
    int favouriteNumber = 1729;
    cout << "Result when writing an int directly to cout: " << favouriteNumber << endl;

    // Write an int to a file.
//    std::ofstream outputFile("out.txt");
//    outputFile << "Result when writing an int to file: " << favouriteNumber << endl;

    // Write method to take any ostream
    std::ofstream fileOut("out.txt");

    writeToStream(cout, favouriteNumber);
    writeToStream(fileOut, favouriteNumber + 1);
    return 0;
}
