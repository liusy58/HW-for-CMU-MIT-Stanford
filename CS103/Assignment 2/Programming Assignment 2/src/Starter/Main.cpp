#include "LogicInternal.h"
#include "LogicParser.h"
#include "LogicVisualizer.h"
#include "TheWindow.h"
#include "TestDriver.h"
#include "ThisButNotThat.h"
#include "ginteractors.h"
#include "gevents.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <memory>
#include "simpio.h"
#include "strlib.h"
#include "filelib.h"
using namespace std;

/* Everything in here is private to this file. */
namespace {   
    const string kButtonFont = "Monospace-BOLD-24";
    
    /* The specific test cases we're going to run. */
    const vector<NamedFunction> kTestFunctions = {
        { isFormulaTrueFor_partI,   "Q3 Part (i)" },
        { isFormulaTrueFor_partII,  "Q3 Part (ii)" },
        { isFormulaTrueFor_partIII, "Q3 Part (iii)" },
        { isFormulaTrueFor_partIV,  "Q3 Part (iv)" },
        { isFormulaTrueFor_partV,   "Q3 Part (v)" },
        { isFormulaTrueFor_partVI,  "Q3 Part (vi)" },
        { this_partI,               "Q6 This (i)" },
        { that_partI,               "Q6 That (i)" },
        { this_partII,              "Q6 This (ii)" },
        { that_partII,              "Q6 That (ii)" },
        { this_partIII,             "Q6 This (iii)" },
        { that_partIII,             "Q6 That (iii)" },
        { this_partIV,              "Q6 This (iv)" },
        { that_partIV,              "Q6 That (iv)" },
        { this_partV,               "Q6 This (v)" },
        { that_partV,               "Q6 That (v)" },
    };

    /* Given a directory, returns a list of all people files in that directory. */
    vector<string> filesIn(const string& directory) {
        /* Begin with a list of all files. */
        vector<string> allFiles;
        listDirectory(directory, allFiles);

        /* Filter down to just those that contain the suffix .people. */
        allFiles.erase(remove_if(allFiles.begin(), allFiles.end(), [](string filename) {
                           return !endsWith(filename, ".people");
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
    vector<string> testFileNames() {
        return combine(filesIn("."), filesIn("Sample"));
    }

    /* Returns a list of all the test cases that need to be run. */
    vector<NamedSource> testCases() {
        vector<NamedSource> result;
        for (string filename: testFileNames()) {
            result.push_back({ filename, make_shared<ifstream>(filename) });
        }
        return result;
    }

    /* Creates a button with the given label and styles it appropriately. */
    GButton* makeButton(const string& label) {
        GButton* result = new GButton(label);
        result->setFont(kButtonFont);
        return result;
    }
}

int main() {
    auto results = runAllTests(testCases(), kTestFunctions);
    if (results.empty()) {
        error("No test cases found.");
    }

    /* Set up buttons. */
    GButton* prev = makeButton("<<");
    GButton* next = makeButton(">>");

    theWindow().addToRegion(prev, "SOUTH");
    theWindow().addToRegion(next, "SOUTH");

    size_t index = 0;
    while (true) {
        visualizeResults(results[index]);

        GEvent e = waitForEvent(ACTION_EVENT);
        if (e.getEventClass() == ACTION_EVENT) {
            GObject* source = GActionEvent(e).getSource();

            /* Step forwards or backwards using modular arithmetic! */
            if (source == prev) {
                index = (index + results.size() - 1) % results.size();
            } else if (source == next) {
                index = (index + 1) % results.size();
            } else {
                error("An unknown button was pressed.");
            }
        }
    }

    return 0; // Unreachable; silences compiler errors
}
