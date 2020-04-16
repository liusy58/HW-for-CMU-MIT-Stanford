#include <iostream>
#include <sstream>
#include <vector>


using std::cout;    using std::endl;
using std::cin;     using std::string;
using std::vector;


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

template <typename DataType>
DataType getType() {
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
         * Try getting an DataType from the stream. If this is not succesful
         * then user input was not a valid input.
         */
        DataType result;
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
                 * Input was succesfully converted to DataType with no
                 * trailing stuff at the end.
                 */
                return result;
            }
        } else {
            cout << "Not a valid input. Try again." << endl;
        }
    }
}



int main() {
    /*
     * The type in the angle bracets specifies how the
     * template will get instantiated.
     */
    cout << "Enter integer: ";
    int a = getType<int>();
    cout << "Enter double: ";
    double b = getType<double>();

    cout << "Int: " << a << endl;
    cout << "Double: " << b << endl;
}
