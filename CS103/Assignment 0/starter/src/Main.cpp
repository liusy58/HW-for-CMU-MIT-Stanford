#include "Answers.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <cstdint>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Type: nat
 *
 * A type representing a natural number, the same way that int represents an integer.
 */
using nat = uint32_t;

/* Displays a nice intro message describing what this program does. */
void showIntro() {
    cout << "Welcome to CS103!" << endl;
    cout << "This program reads a positive natural number n, then outputs a base-10" << endl;
    cout << "number made only of 0s and 1s that's a multiple of n." << endl;
    cout << endl;
    cout << "This program works using a technique called the pigeonhole principle," << endl;
    cout << "which we'll learn about later on. The idea is that there are only n" << endl;
    cout << "possible remainders a number can leave when divided by n. Therefore," << endl;
    cout << "if we look at the remainders of the numbers 1, 11, 111, 1111, 11111," << endl;
    cout << "etc., and look at n+1 total numbers, two of them must have the same" << endl;
    cout << "remainder when divided by n. If we subtract the smaller of those" << endl;
    cout << "numbers from the bigger of the two numbers, then the result is a" << endl;
    cout << "number made purely of 0s and 1s whose remainder when divided by n" << endl;
    cout << "is zero - in other words, it's a multiple of n!" << endl;
    cout << endl;
}

/* Prompts the user for a positive natural number, returning whatever value is entered. */
nat getPositiveInteger(const string& prompt) {
    static const nat kMaxValue = 10000;
    while (true) {
        int result = getInteger(prompt);
        if (result <= 0) {
            cerr << "Please enter a positive number." << endl;
        } else {
            if (nat(result) <= kMaxValue) return nat(result);
            else cerr << "Please enter a value less than or equal to " << kMaxValue << "." << endl;
        }
    }
}

/* Computes and returns a number that's a multiple of the specified value that's made
 * purely of 0s and 1s. The value is returned as a string because it's likely going to
 * be way too large to fit into an integer.
 */
string multipleOf(nat n) {
    /* Map associating remainders mod n with the number of digits in a number of the form
     * 1111...1.
     */
    unordered_map<nat, nat> remainders;

    /* Track the current number of digits and the current remainder. The initial number (1)
     * has 1 digit and its remainder is 1, unless n = 1 in which case the remainder is 0.
     */
    nat digits = 1;
    nat remainder = 1 % n; // n could be equal to 1.

    /* This loop is technically a while (true) loop, but it's guaranteed to terminate after
     * at most n+1 steps.
     */
    while (true) {
        /* If there's a collision in the map with this remainder, we've found a number that
         * works and we can stop!
         */
        if (remainders.count(remainder)) {
            /* Make a number from the digit count. The number of 1s is the difference
             * between the existing number of 1s and the stored number of 1s, and the
             * number of 0 is the stored number.
             */
            return string(digits - remainders[remainder], '1') + string(remainders[remainder], '0');
        }

        /* Otherwise, update the map. */
        remainders[remainder] = digits;

        /* Simulate appending a 1 to the end of this number. That's equivalent to
         * multiplying by ten and adding 1.
         */
        remainder = (10 * remainder + 1) % n;
        digits++;
    }
}

int main() {
    showIntro();
    nat n = getPositiveInteger("Enter a positive natural number: ");
    string digits = multipleOf(n);
    cout << "The number " << digits << " is a multiple of " << n << "." << endl;

    return 0;
}
