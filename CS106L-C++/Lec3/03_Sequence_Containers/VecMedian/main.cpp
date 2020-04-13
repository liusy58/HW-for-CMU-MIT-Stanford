#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;    using std::endl;
using std::cin;    using std::string;
using std::vector;

/*
 * Most containers define the variable type that can
 * be used to store its size. To access the type, you
 * can do container<T>::size_type. This can get annoying
 * to write so we can create an alias/synonym for this
 * type and call it vecsz_t.
 *
 * Side note: Most of the standard library containers define
 * their size_type to be the builtin unsigned integer type
 * called size_t. If you don't want to mess around with these
 * aliases, you are free to just ust size_t everywhere.
 */
using vecsz_t = std::vector<int>::size_type;


int getInteger() {
    while(true) {
        /* First we get a line of input from the user. */
        string line;
        std::getline(cin, line);
        /*
         * We'll again use an istringstream because we only want to pull data
         * out of the stream once we have put the string's contents in it.
         */
        std::istringstream converter(line);
        /*
         * Try getting an int from the stream. If this is not succesful
         * then user input was not a valid input.
         */
        int result;
        if(converter >> result) {
            /*
             * See if we can extract a char from the stream.
             * If so, the user had junk after a valid int in their input.
             */
            char remaining;
            if(converter >> remaining) {
                cout << "Unexpected character. Try again." << endl;
            } else {
                /*
                 * Input was succesfully converted to int with no
                 * trailing stuff at the end.
                 */
                return result;
            }
        } else {
            cout << "Not a valid integer. Try again." << endl;
        }
    }
}


void printVector(const vector<int>& data) {
    for(vecsz_t i = 0; i < data.size(); ++i) {
        cout << data[i] << " ";
    }
    cout << endl;
}


int main() {
    // Read 5 int values into vector
    const int kNumValues = 5;
    vector<int> data;
    for(int i = 0; i < kNumValues; ++i) {
        cout << "Enter value (" << kNumValues - i << " left): ";
        int curr = getInteger();
        data.push_back(curr);       // add to end of vector
    }

    /*
     * We are using the alias we declared earlier as
     * the type of the variable named size.
     */
    vecsz_t size = data.size();

    // If no data was entered, stop
    if(size == 0) {
        cout << "No data entered." << endl;
        return 1;
    }

    /* Sort the vector by taking a range. In this case
     * the range we specify starts at the beginning of data
     * and ends at
     */
    std::sort(data.begin(), data.end());


    // Find median:
    //     if vec size is odd, return middle elem
    //     if vec size is even, return average of middle two elems
    vecsz_t mid = size/2;
    double median;
    if(size % 2 == 0) {
        median = (data[mid - 1] + data[mid])/2.0;
    } else {
        median = data[mid];
    }
    printVector(data);
    cout << "The median of the data is: " << median << endl;

}
