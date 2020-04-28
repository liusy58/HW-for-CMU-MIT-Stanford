#include "BinaryRelations.h"
#include "RelationParser.h"
#include "RelationVisualizer.h"
#include "TheWindow.h"
#include "TestDriver.h"
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
    const string kButtonFont   = "Monospace-BOLD-24";
    const string kChooserFont  = "Monospace-BOLD-16";
    const double kChooserWidth = 300;
    
    /* The specific test cases we're going to run. */
    const vector<NamedFunction> kTestFunctions = {
        { isReflexive,           "Reflexive" },
        { isSymmetric,           "Symmetric" },
        { isTransitive,          "Transitive" },
        { isIrreflexive,         "Irreflexive" },
        { isAsymmetric,          "Asymmetric" },
        { isEquivalenceRelation, "Equivalence Relation" },
        { isStrictOrder,         "Strict Order" },
    };

    /* Given a directory, returns a list of all relation files in that directory. */
    vector<string> filesIn(const string& directory) {
        /* Begin with a list of all files. */
        vector<string> allFiles;
        listDirectory(directory, allFiles);

        /* Filter down to just those that contain the suffix .relation. */
        allFiles.erase(remove_if(allFiles.begin(), allFiles.end(), [](string filename) {
                           return !endsWith(filename, ".relation");
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

    /* Creates our lovely dropdown chooser. */
    GChooser* makeChooser() {
        GChooser* result = new GChooser();
        result->addItems({
            "-",
            "Show Equivalence Classes",
            "Show Covering Relation",
        });
        result->setFont(kChooserFont);
        result->setSize(kChooserWidth, result->getHeight());
        return result;
    }

    /* Sequence of colors to use for equivalence classes. */
    const vector<Color> kNodeColors = {
        { 0xFF, 0x00, 0x00 },
        { 0x00, 0x00, 0xFF },
        { 0x00, 0xFF, 0x00 },
        { 0xFF, 0xFF, 0x00 },
        { 0xFF, 0x00, 0xFF },
        { 0x00, 0xFF, 0xFF },
        { 0xFF, 0x80, 0x00 },
        { 0x80, 0x00, 0x00 },
        { 0x00, 0x00, 0x80 },
        { 0x00, 0x80, 0x00 },
        { 0x80, 0x80, 0x00 },
        { 0x80, 0x00, 0x80 },
        { 0x00, 0x80, 0x80 },
        { 0x80, 0x40, 0x00 },
        { 0x80, 0x80, 0x80 },
        { 0x40, 0x00, 0x00 },
        { 0x00, 0x00, 0x40 },
        { 0x00, 0x40, 0x00 },
        { 0x40, 0x40, 0x00 },
        { 0x40, 0x00, 0x40 },
        { 0x00, 0x40, 0x40 },
        { 0x40, 0x20, 0x00 },
        { 0x40, 0x40, 0x40 }
    };

    /* Colors to use to draw the circles around objects. */
    const Color kObjectColor = { 0x80, 0xA0, 0xFF };
    const Color kEdgeColor   = { 0x00, 0x00, 0x00 };

    /* Colors to use for edges when we're viewing the covering relation. */
    const Color kIncludedEdgeColor = { 0x00, 0x00, 0x80 };
    const Color kExcludedEdgeColor = { 0xC0, 0xC0, 0xC0 };

    /* Given a relation, colors each node the default color. */
    map<int, Color> defaultNodeColorsFor(const Relation& R) {
        map<int, Color> result;

        for (auto elem: R.domain) {
            result[elem] = kObjectColor;
        }

        return result;
    }

    /* Given an equivalence relation, returns colors for its equivalence classes. If not all
     * nodes are assigned colors or there's something else wrong with the relation, this
     * throws an exception.
     */
    map<int, Color> colorEquivalenceClassesOf(const Relation& R) {
        auto classes = equivalenceClassesOf(R);

        /* Confirm each node shows up once and exactly once. Keys are elements, values
         * are indices.
         */
        map<int, size_t> classIDs;
        for (size_t i = 0; i < classes.size(); i++) {
            /* There should be no empty classes. */
            if (classes[i].empty()) {
                error("You included an empty equivalence class.");
            }

            for (int elem: classes[i]) {
                /* Make sure there are no duplicates. */
                if (classIDs.count(elem)) {
                    error("You assigned " + to_string(elem) + " to more than one equivalence class.");
                }

                /* Make sure that this is actually an element in the relation. */
                if (!R.domain.count(elem)) {
                    error("You included " + to_string(elem) + ", which is not in this relation.");
                }
                classIDs[elem] = i;
            }
        }

        /* Make sure we have one element per item. */
        if (classIDs.size() != R.domain.size()) {
            error("You did not assign all elements of the domain to an equivalence class.");
        }

        /* Conver to a color map. */
        map<int, Color> result;
        for (const auto& entry: classIDs) {
            if (entry.second >= kNodeColors.size()) {
                error("Our visualizer maxes out at " + to_string(kNodeColors.size()) + " colors; sorry!");
            }
            result[entry.first] = kNodeColors[entry.second];
        }

        return result;
    }

    /* Given a relation, returns colors to be used for each node. */
    map<int, Color> nodeColorsFor(const Relation& R, GChooser* chooser, string& errorMessage) {
        if (chooser->getSelectedItem() == "Show Equivalence Classes") {
            /* See if this is an equivalence relation. If so, color the equivalence
             * classes.
             */
            try {
                if (isEquivalenceRelation(R)) {
                    return colorEquivalenceClassesOf(R);
                } else {
                    errorMessage = "(We can only show equivalence classes of equivalence relations.)";
                }
            } catch (const exception& e) {
                errorMessage = e.what();
            }
        }
        return defaultNodeColorsFor(R);
    }

    /* Given a binary relation, displays the default edge colors for that relation. */
    map<Pair, Color> defaultEdgeColorsFor(const Relation& R) {
        map<Pair, Color> result;

        for (auto elem: R.r) {
            result[elem] = kEdgeColor;
        }

        return result;
    }


    /* Given a strict order, colors its covering relation. */
    map<Pair, Color> colorCoveringRelationOf(const Relation& R) {
        /* Start by computing the covering relation. */
        Relation cover = coverOf(R);

        /* Confirm the underlying domain is the same. */
        if (cover.domain != R.domain) {
            error("Covering relation and original relation have different domains.");
        }

        /* Confirm that each edge in the cover was present in the original. */
        if (!includes(R.r.begin(), R.r.end(), cover.r.begin(), cover.r.end())) {
            error("Your reported covering relation is not a subset of the original relation.");
        }

        /* Color everything according to whether it's present in the cover. */
        map<Pair, Color> result;
        for (auto xRy: R.r) {
            result[xRy] = (cover.r.count(xRy)? kIncludedEdgeColor : kExcludedEdgeColor);
        }
        return result;
    }

    /* Given a relation, returns colors to be used for each edge. */
    map<Pair, Color> edgeColorsFor(const Relation& R, GChooser* chooser, string& errorMessage) {
        if (chooser->getSelectedItem() == "Show Covering Relation") {
            /* See if this is a strict order. If so, highlight the covering relation. */
            try {
                if (isStrictOrder(R)) {
                    return colorCoveringRelationOf(R);
                } else {
                    errorMessage = "(We only show cover relations for strict orders.)";
                }
            } catch (const exception& e) {
                errorMessage = e.what();
            }
        }

        return defaultEdgeColorsFor(R);
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
    GChooser* chooser = makeChooser();

    theWindow().addToRegion(prev,    "SOUTH");
    theWindow().addToRegion(chooser, "SOUTH");
    theWindow().addToRegion(next,    "SOUTH");

    size_t index = 0;
    while (true) {
        /* Draw the current graph and test results, highlighted with whatever colors
         * are appropriate based on the user selection.
         */
        string errorMessage;
        auto nodeColors = nodeColorsFor(results[index].relation, chooser, errorMessage);
        auto edgeColors = edgeColorsFor(results[index].relation, chooser, errorMessage);
        visualizeRelation(results[index], errorMessage, nodeColors, edgeColors);

        GEvent e = waitForEvent(ACTION_EVENT);
        if (e.getEventClass() == ACTION_EVENT) {
            GObject* source = GActionEvent(e).getSource();

            /* Step forwards or backwards using modular arithmetic! */
            if (source == prev) {
                index = (index + results.size() - 1) % results.size();
            } else if (source == next) {
                index = (index + 1) % results.size();
            } else if (source != chooser) {
                error("An unknown button was pressed.");
            }
        }
    }

    return 0; // Unreachable; silences compiler errors
}
