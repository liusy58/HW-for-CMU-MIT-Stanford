#include "SetInternal.h"
#include "ObjectParser.h"
#include "TestDriver.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include "simpio.h"
#include "strlib.h"
#include "filelib.h"
#include "console.h"
using namespace std;

/* Everything in here is private to this file. */
namespace {   
    /* Padding sizes for various outputs. */
    const int kTestNameWidth = 16;
    const int kFilenameWidth = 30;

    /* The specific test cases we're going to run. */
    const vector<NamedFunction> kTestFunctions = {
        { isElementOf,              "S in T" },
        { isSubsetOf,               "S subset T" },
        { areDisjointSets,          "S n T = {}" },
        { isSingletonOf,            "S = {T}" },
        { isElementOfPowerSet,      "S in P(T)" },
        { isSubsetOfPowerSet,       "S subset P(T)" },
        { isSubsetOfDoublePowerSet, "S subset P(P(T))" },
    };

    /* Asks the user to choose a object, whether it's from the provided helper files or via
     * direct input
     */
    string userChooseObject(shared_ptr<istream>& input, const string& prompt) {
        while (true) {
            string userInput = getLine(prompt);

            /* If the filename ends in .object, try reading it as a file. */
            if (endsWith(userInput, ".object")) {
                input = make_shared<ifstream>(userInput);
                if (!*input) {
                    cerr << "Sorry, I can't open that file." << endl;
                    continue;
                }
            }
            /* Otherwise, try treating it as a string to parse. */
            else {
                input = make_shared<istringstream>(userInput);
            }

            /* Make sure the contents are legit. */
            try {
                /* Try loading an object. If it succeeds, great! But be sure to rewind
                 * things so that we can scan it again.
                 */
                (void) loadObject(*input);
                rewindStream(*input);

                return userInput;
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
    }

    /* Given a Result, returns a string representation of that result. */
    string toString(Result r) {
        if (r == Result::TRUE)  return "true";
        if (r == Result::FALSE) return "false";
        if (r == Result::ERROR) return "error";
        Utilities::error("Unknown result type?");
    }

    /* Given a directory, returns a list of all object files in that directory. */
    vector<string> filesIn(const string& directory) {
        /* Begin with a list of all files. */
        vector<string> allFiles;
        listDirectory(directory, allFiles);

        /* Filter down to just those that contain the suffix .object. */
        allFiles.erase(remove_if(allFiles.begin(), allFiles.end(), [](string filename) {
                           return !endsWith(filename, ".object");
                       }), allFiles.end());

        /* Prepend the directory name to each file... unless we're in the home
         * directory.
         */
        if (directory != ".") {
            for (auto& filename: allFiles) {
                filename = directory + "/" + filename;
            }
        }

        return allFiles;
    }

    /* Given a list of containers, combines them all into a single vector. */

    /* Base case: Combining an empty list produces an empty list. */
    vector<string> combine() {
        return {};
    }

    /* Recursive step: Combining n+1 lists combines the last n, then appends them
     * to the first.
     */
    template <typename First, typename... Rest>
    vector<string> combine(First first, const Rest&... last) {
        auto remainder = combine(last...);
        first.insert(first.end(), remainder.begin(), remainder.end());

        return first;
    }

    /* Returns all files that end in the .people suffix, which we'll use as our test cases. */
    vector<string> objectFileNames() {
        return combine(filesIn("."), filesIn("Sample"));
    }

    /* Lists all objects available in the res/ directory. */
    void viewObjects() {
        for (string filename: objectFileNames()) {
            cout << setw(kFilenameWidth) << filename << ": " << flush;

            /* Open the file and confirm we can read it. */
            ifstream input(filename);
            if (!input) {
                cerr << "File exists, but cannot be opened (?)" << endl;
                continue;
            }

            /* Display the contents. */
            try {
                auto obj = loadObject(input);
                cout << obj << endl;
            } catch (const std::exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
    }

    /* Runs all tests on a pair of sets provided by the user. */
    void runTests() {
        std::shared_ptr<istream> sSource;
        std::shared_ptr<istream> tSource;
        string sName = userChooseObject(sSource, "Enter object S (or the name of a file containing S): ");
        string tName = userChooseObject(tSource, "Enter object T (or the name of a file containing T): ");

        auto results = runAllTests({ { sName, tName, sSource, tSource } }, kTestFunctions);
        for (TestResults result: results) {
            for (NamedResult oneTest: result.results) {
                cout << "  " << setw(kTestNameWidth) << oneTest.name << ": " << flush;
                if (oneTest.result != Result::ERROR) {
                    cout << toString(oneTest.result) << endl;
                } else {
                    cerr << "error: " << oneTest.message << endl;
                }
            }
        }
    }

    /* Type representing a menu option. */
    enum MenuOption {
        VIEW_OBJECTS = 1,
        RUN_TESTS,
        QUIT
    };

    /* Displays all the menu options. */
    void displayMenu() {
        cout << "  " << VIEW_OBJECTS  << ": View all objects contained in the bundled files." << endl;
        cout << "  " << RUN_TESTS     << ": Run your functions on a pair of objects." << endl;
        cout << "  " << QUIT          << ": Quit this program." << endl;
    }

    /* Handles a response from the menu. */
    void handleMenuResponse() {
        while (true) {
            MenuOption option = MenuOption(getInteger("Enter a choice: "));
            switch (option) {
            case VIEW_OBJECTS:
                viewObjects();
                return;
            case RUN_TESTS:
                runTests();
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
    cout << "CS103: Programming Assignment for Problem Set 1" << endl;

    while (true) {
        displayMenu();
        handleMenuResponse();
        cout << endl;
        cout << endl;
    }

    return 0; // Unreachable; silences compiler errors
}
