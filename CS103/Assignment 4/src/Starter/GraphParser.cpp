#include "GraphParser.h"
#include "GraphInternal.h"
#include "Utilities.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace {
    struct ParsedLine {
        string type;
        vector<string> args;
    };

    /* Given a line of text from a file, parses that line into a more structured
     * format. If the line can't be parsed, reports an error.
     */
    ParsedLine parse(const string& line) {
        ParsedLine result;

        /* The expected format is
         *
         *    SomeFunctionSymbol(ArgList)
         *
         * So let's grab everything up to that first parenthesis.
         */
        auto openIndex = line.find('(');
        if (openIndex == string::npos) Utilities::error("Couldn't find an open parenthesis in this line.");
        result.type = Utilities::trim(line.substr(0, openIndex));

        /* Find the close parenthesis that matches this open parenthesis. Make sure that it's
         * at the very end.
         */
        auto closeIndex = line.find(')', openIndex);
        if (closeIndex != line.size() - 1) Utilities::error("Extra tokens found after close parenthesis.");

        /* Split the inner part of the string to get the arguments. */
        result.args = Utilities::stringSplit(string(line.begin() + openIndex + 1, line.end() - 1), ',');

        /* Trim all leading and trailing whitespace from each argument. */
        for (auto& arg: result.args) {
            arg = Utilities::trim(arg);
            if (arg.empty()) Utilities::error("Empty argument found in parameter list.");
        }
        return result;
    }

    /* Given a command to define a node, goes and defines that node, reporting an error
     * if this isn't possible.
     */
    void processNode(const vector<string>& args, Graph& graph, map<string, Node>& nameMap) {
        /* Confirm that there's a single argument. */
        if (args.size() != 1) Utilities::error("The Node predicate requires exactly one argument.");

        /* If this node already exists, there's nothing to do. */
        if (nameMap.count(args[0])) return;

        /* Create an insert a new node. */
        auto* node = new RealNode { args[0] };
        graph[node] = {}; // No edges... yet!
        nameMap[args[0]] = node;
    }

    /* Given a node name, either returns that node or reports that it doesn't yet
     * exist.
     */
    Node nodeNamed(const string& name, map<string, Node>& nameMap) {
        auto result = nameMap.find(name);
        if (result == nameMap.end()) Utilities::error("Node doesn't exist (yet?): " + name);
        return result->second;
    }

    /* Given a command to introduce an edge into the graph, adds the edge, reporting an
     * error if it's not possible to do so.
     */
    void processEdge(const vector<string>& args, Graph& graph, map<string, Node>& nameMap) {
        /* Confirm that there's two arguments. */
        if (args.size() != 2) Utilities::error("The Edge predicate requires exactly two arguments.");

        auto first  = nodeNamed(args[0], nameMap);
        auto second = nodeNamed(args[1], nameMap);

        /* Self-loops aren't allowed. */
        if (first == second) Utilities::error("Undirected graphs cannot contain self-loops.");

        /* Edges are bidirectional. */
        graph[first].insert(second);
        graph[second].insert(first);
    }
}

/* Given a stream that contains a definition of a graph, parses the graph from
 * the stream and returns it (or triggers an error if the file is malformed.)
 */
Graph loadGraph(istream& source) {
    Graph result;
    map<string, Node> nameMap;

    for (string line; getline(source, line); ) {
        /* If there's a pound symbol, delete everything after it. */
        line.erase(find(line.begin(), line.end(), '#'), line.end());

        /* Trim our line to remove any stray whitespace. */
        line = Utilities::trim(line);

        /* If the line is empty, it's either blank or it was a comment
         * and we can safely skip it.
         */
        if (line.empty()) continue;

        /* Determine what kind of line we're looking at. */
        ParsedLine parsedLine = parse(line);

        if (parsedLine.type == "Node") {
            processNode(parsedLine.args, result, nameMap);
        } else if (parsedLine.type == "Edge") {
            processEdge(parsedLine.args, result, nameMap);
        } else {
            Utilities::error("Unknown statement type: [" + line + "]");
        }
    }

    return result;
}
