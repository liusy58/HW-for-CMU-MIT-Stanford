#include "LogicParser.h"
#include "LogicInternal.h"
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
        if (openIndex == string::npos) Utilities::error("Couldn't find an open parenthesis in input line.");
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

    /* Given a command to define a person, goes and defines that person, reporting an error
     * if this isn't possible.
     */
    void processPerson(const vector<string>& args, Group& group) {
        /* Confirm that there's a single argument. */
        if (args.size() != 1) Utilities::error("The Person predicate requires exactly one argument.");

        /* If this person already exists, there's nothing to do. */
        if (group.count(args[0])) return;

        /* Create an insert a new person, who is by default not happy. */
        RealPerson* person = new RealPerson { args[0], false, {} };
        group[args[0]] = person;
    }

    /* Given a person's name, either returns that person or reports that they don't yet
     * exist.
     */
    RealPerson* personNamed(const string& name, Group& group) {
        auto result = group.find(name);
        if (result == group.end()) Utilities::error("Person doesn't exist (yet?): " + name);
        return result->second;
    }

    /* Given a command to mark a person happy, does so and reports an error if that's not
     * possible.
     */
    void processHappy(const vector<string>& args, Group& group) {
        /* Confirm that there's a single argument. */
        if (args.size() != 1) Utilities::error("The Happy predicate requires exactly one argument.");

        personNamed(args[0], group)->isHappy = true;
    }

    /* Given a command to say one person loves another, makes that the case and reports
     * an error if that's not possible.
     */
    void processLove(const vector<string>& args, Group& group) {
        /* Confirm that there's two arguments. */
        if (args.size() != 2) Utilities::error("The Loves predicate requires exactly two arguments.");

        personNamed(args[0], group)->loves.insert(personNamed(args[1], group));
    }
}

/* Given a stream that contains a definition of a group of people, parses
 * that group of people into a map from names to people. Does what might be
 * best described as pedantic error-checking.
 */
Group loadGroup(istream& source) {
    Group result;

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

        if (parsedLine.type == "Person") {
            processPerson(parsedLine.args, result);
        } else if (parsedLine.type == "Happy") {
            processHappy(parsedLine.args, result);
        } else if (parsedLine.type == "Loves") {
            processLove(parsedLine.args, result);
        } else {
            Utilities::error("Unknown statement type: [" + line + "]");
        }
    }

    return result;
}
