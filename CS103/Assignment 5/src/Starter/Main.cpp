#include "CoinInternal.h"
#include "TestDriver.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <memory>
#include <sstream>
#include <cassert>
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "console.h"
using namespace std;

/* Private helper functions. */
namespace {   
    /* For memory reasons, we have to cap the maximum value of n at something
     * reasonable. I picked 14; feel free to change this, but do so at your
     * own risk!
     */
    const size_t kMaxN = 14;

    /* Prompts the user for the number n in the base of an exponent. */
    size_t getN() {
        while (true) {
            int result = getInteger("Enter n: ");
            if (0 <= result && size_t(result) <= kMaxN) {
                return size_t(result);
            } else {
                cerr << "Please enter an integer between 0 and " << kMaxN << endl;
            }
        }
    }

    /* Computes 3^n, recursively, of course! */
    size_t threeToThe(size_t n) {
        if (n == 0) return 1;
        return 3 * threeToThe(n - 1);
    }

    /* Prompts the user to choose the index of a counterfeit coin. */
    int getCounterfeitIndex(size_t numCoins, bool allowNone) {
        /* If there are no coins, we HAVE to have no counterfeit. */
        if (numCoins == 0) {
            assert(allowNone);
            return -1;
        }

        cout << "Enter the index of the counterfeit coin, between 0 and " << (numCoins - 1) << ", inclusive." << endl;
        if (allowNone) cout << "Or, type 'none' if you don't want a counterfeit." << endl;
        cout << "Or, just hit ENTER if you want us to pick a random coin." << endl;

        while (true) {
            string input = trim(getLine("Your choice: "));

            /* Empty line means "pick randomly." */
            if (input.empty()) {
                return randomInteger(0, int(numCoins) - 1);
            }
            /* 'none' means None. */
            else if (toLowerCase(input) == "none" && allowNone) {
                return -1;
            }
            /* Otherwise, this should be an integer. */
            else if (!stringIsInteger(input)) {
                cerr << "Sorry, I didn't understand that." << endl;
            } else {
                int index = stringToInteger(input);
                if (index >= 0 && index < int(numCoins)) {
                    return index;
                } else {
                    cerr << "Sorry, that number is out of range." << endl;
                }
            }
        }
    }

    /* Maximum number of coins to display in one weighing. This is just for display
     * purposes and has no internal effects.
     */
    const size_t kMaxCoins = 7;

    /* Given an index of a coin, returns the name of that coin. */
    string nameFor(size_t value) {
        return to_string(value);
    }

    /* Converts a vector<Coin> into a human-readable representation. */
    string toString(const vector<Coin>& coins) {
        ostringstream result;

        result << "[ ";

        /* If we fit, just list everything off. */
        if (coins.size() <= kMaxCoins) {
            for (Coin c: coins) {
                result << nameFor(c->index) << " ";
            }
        }
        /* Otherwise, list off the first few options. */
        else {
            for (size_t i = 0; i < kMaxCoins - 1; i++) {
                result << nameFor(coins[i]->index) << " ";
            }
            result << " ... ";
            result << nameFor(coins.back()->index);
        }

        result << "]";
        return result.str();
    }

    /* Displays that a weighing is being made. */
    void reportWeighing(size_t numWeighings,
                        const vector<Coin>& left, const vector<Coin>& right,
                        int result) {
        cout << "Weighing #" << numWeighings << endl;
        cout << "  " << toString(left) << " vs. " << toString(right) << endl;
        cout << "Result: ";
        if (result == -1) {
            cout << "Left side heavier." << endl;
        } else if (result == +1) {
            cout << "Right side heavier." << endl;
        } else {
            cout << "Both sides equal." << endl;
        }
    }

    /* Runs the student's solution on a given set of parameters. */
    void runTests(size_t numWeighings, size_t numCoins, int counterfeitIndex,
                  function<Coin(vector<Coin>, Balance)> studentFn) {
        cout << "Running test: determine that "
             << (counterfeitIndex == -1? "no coin" : "coin " + nameFor(counterfeitIndex))
             << " of " << numCoins
             << " is counterfeit in " << numWeighings << " weighing"
             << (numWeighings == 1? "" : "s") << "." << endl;

        auto result = runAllTests({ {"", numCoins, numWeighings, counterfeitIndex} },
                                  studentFn, reportWeighing)[0];
        if (result.result == Result::ERROR) {
            cerr << "An error occurred: " << result.message;
        } else {
            if (result.coin == None) {
                cout << "Your answer: No counterfeit exists." << endl;
            } else {
                cout << "Your answer: Coin " << nameFor(result.coin->index) << " is counterfeit." << endl;
            }

            if (result.result == Result::PASS) {
                cout << "Correct!" << endl;
            } else {
                cerr << result.message << endl;
            }
        }
    }

    void findCounterfeit() {
        cout << "Find a counterfeit out of a group of 3^n coins." << endl;
        size_t n  = getN();
        size_t numCoins = threeToThe(n);
        int index = getCounterfeitIndex(numCoins, false);

        /* Run the student code and report the result. */
        runTests(n, numCoins, index, counterfeitIn);
    }

    void findPossibleCounterfeit() {
        cout << "Find a possible counterfeit out of a group of 3^n - 1 coins." << endl;
        size_t n  = getN();
        size_t numCoins = threeToThe(n) - 1;
        int index = getCounterfeitIndex(numCoins, true);

        /* Run the student code and report the result. */
        runTests(n, numCoins, index, maybeCounterfeitIn);
    }

    /* Type representing a menu option. */
    enum MenuOption {
        FIND_COUNTERFEIT = 1,
        FIND_OPTIONAL_COUNTERFEIT,
        QUIT
    };

    /* Displays all the menu options. */
    void displayMenu() {
        cout << "  " << FIND_COUNTERFEIT          << ": Test your code to find a definite counterfeit." << endl;
        cout << "  " << FIND_OPTIONAL_COUNTERFEIT << ": Test your code to find a possible counterfeit." << endl;
        cout << "  " << QUIT                      << ": Quit this program." << endl;
    }

    /* Handles a response from the menu. */
    void handleMenuResponse() {
        while (true) {
            MenuOption option = MenuOption(getInteger("Enter a choice: "));
            switch (option) {
            case FIND_COUNTERFEIT:
                findCounterfeit();
                return;
            case FIND_OPTIONAL_COUNTERFEIT:
                findPossibleCounterfeit();
                return;
            case QUIT:
                exit(EXIT_SUCCESS);
                return; // Unreachable; silences warnings
            default:
                cerr << "Please enter a valid selection." << endl;
            }
        }
    }
}

int main() {
    cout << "CS103: Programming Assignment for Problem Set 5" << endl;

    while (true) {
        displayMenu();
        handleMenuResponse();
        cout << endl;
        cout << endl;
    }

    return 0; // Unreachable; silences compiler errors
}
