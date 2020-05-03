#include "GraphInternal.h"
#include "GraphParser.h"
#include "GraphVisualizer.h"
#include "GraphProperties.h"
#include "TheWindow.h"
#include "Utilities.h"
#include "ginteractors.h"
#include "gevents.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <memory>
#include <functional>
#include "simpio.h"
#include "strlib.h"
#include "filelib.h"
using namespace std;

/* Everything in here is private to this file. */
namespace {   
    const string kButtonFont   = "Monospace-BOLD-24";
    const string kChooserFont  = "Monospace-BOLD-16";
    const double kChooserWidth = 300;

    /* Type representing a named graph. */
    struct NamedGraph {
        Graph G;
        string name;
    };

    /* Given a directory, returns a list of all graph files in that directory. */
    vector<string> graphFilesIn(const string& directory) {
        /* Begin with a list of all files. */
        vector<string> allFiles;
        listDirectory(directory, allFiles);

        /* Filter down to just those that contain the suffix .relation. */
        allFiles.erase(remove_if(allFiles.begin(), allFiles.end(), [](string filename) {
            return !endsWith(filename, ".graph");
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

    /* Returns a list of all the graph files to display. */
    vector<string> graphFileNames() {
        return combine(graphFilesIn("."), graphFilesIn("Sample"));
    }

    /* Returns a list of all the test cases that need to be run. */
    vector<NamedGraph> allGraphs() {
        vector<NamedGraph> result;
        for (string filename: graphFileNames()) {
            ifstream input(filename);
            if (!input) error("Couldn't open graph file " + filename);

            result.push_back({ loadGraph(input), filename });
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
            "Max Independent Set",
            "Min Vertex Cover",
            "Max Clique",
            "Min Vertex Coloring"
        });
        result->setFont(kChooserFont);
        result->setSize(kChooserWidth, result->getHeight());
        return result;
    }

    /* Sequence of colors to use in k-vertex-colorings. */
    const vector<RealColor> kNodeColors = {
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

    /* Default node color. */
    const RealColor kDefaultColor = { 0xB0, 0xB0, 0xB0 };

    /* Highlight colors. */
    const RealColor kIndependentSetColor = { 0xFF, 0xC0, 0x40 };
    const RealColor kVertexCoverColor    = { 0xA0, 0x20, 0x20 };
    const RealColor kCliqueColor         = { 0x20, 0x20, 0xA0 };

    /* Colors every node in the graph the default color. */
    map<Node, Color> allDefault(const Graph& graph) {
        map<Node, Color> result;

        for (const auto& entry: graph) {
            result[entry.first] = &kDefaultColor;
        }

        return result;
    }

    /* Computes a maximum independent set and colors all the nodes accordingly. */
    map<Node, Color> colorMaxIndependentSet(const Graph& graph) {
        map<Node, Color> result;

        for (const auto& entry: graph) {
            result[entry.first] = &kDefaultColor;
        }

        for (Node n: largestIndependentSetIn(graph, isIndependentSet)) {
            result[n] = &kIndependentSetColor;
        }

        return result;
    }

    /* Computes a minimum vertex cover and colors all the nodes accordingly. */
    map<Node, Color> colorMinVertexColor(const Graph& graph) {
        map<Node, Color> result;

        for (const auto& entry: graph) {
            result[entry.first] = &kDefaultColor;
        }

        for (Node n: minVertexCoverIn(graph, isVertexCover)) {
            result[n] = &kVertexCoverColor;
        }

        return result;
    }

    /* Computes a max clique and colors all the nodes accordingly. */
    map<Node, Color> colorMaxClique(const Graph& graph) {
        map<Node, Color> result;

        for (const auto& entry: graph) {
            result[entry.first] = &kDefaultColor;
        }

        for (Node n: largestCliqueIn(graph, isClique)) {
            result[n] = &kCliqueColor;
        }

        return result;
    }

    /* Given a graph and a property, returns the color associated with that property. */
    map<Node, Color> colorsFor(const Graph& graph, const string& property) {
        if (property == "-") {
            return allDefault(graph);
        } else if (property == "Max Independent Set") {
            return colorMaxIndependentSet(graph);
        } else if (property == "Min Vertex Cover") {
            return colorMinVertexColor(graph);
        } else if (property == "Max Clique") {
            return colorMaxClique(graph);
        } else if (property == "Min Vertex Coloring") {
            return kVertexColor(graph, kNodeColors, isKVertexColoring);
        } else {
            Utilities::error("Unknowng property: " + property);
        }
    }
}

int main() {
    auto graphs = allGraphs();
    if (graphs.empty()) {
        error("No graphs found.");
    }

    /* Set up controls. */
    GButton*  prev = makeButton("<<");
    GButton*  next = makeButton(">>");
    GChooser* chooser = makeChooser();

    theWindow().addToRegion(prev, "SOUTH");
    theWindow().addToRegion(chooser, "SOUTH");
    theWindow().addToRegion(next, "SOUTH");

    size_t index = 0;
    while (true) {
        /* Attempt to use student code to color the graph accordingly. If that falls, fall
         * back to boring gray and report an error.
         */
        try {
            auto colors = colorsFor(graphs[index].G, chooser->getSelectedItem());
            visualizeGraph(graphs[index].G, graphs[index].name, "", colors);
        } catch (const exception& e) {
            visualizeGraph(graphs[index].G, graphs[index].name, string("Error: ") + e.what(), allDefault(graphs[index].G));
        }

        GEvent e = waitForEvent(ACTION_EVENT);
        if (e.getEventClass() == ACTION_EVENT) {
            GObject* source = GActionEvent(e).getSource();

            /* Step forwards or backwards using modular arithmetic! */
            if (source == prev) {
                index = (index + graphs.size() - 1) % graphs.size();
            } else if (source == next) {
                index = (index + 1) % graphs.size();
            } else if (source == chooser) {
                // Do nothing
            } else {
                error("An unknown button was pressed.");
            }
        }
    }

    return 0; // Unreachable; silences compiler errors
}
