#include "RelationParser.h"
#include "BinaryRelations.h"
#include "Utilities.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace {
    struct ParsedLine {
        string type;
        vector<int> args;
    };

    /* Given a line of the format xRy, parses it into a ParsedLine with information
     * about the arguments.
     */
    ParsedLine parseR(const string& line) {
        /* Look for the letter R, which should appear somewhere. */
        auto rIndex = line.find('R');
        if (rIndex == string::npos) Utilities::error("Line looks like it has form xRy, but no R was found.");

        /* Split the string into the "before R" and "after R" parts. */
        string first  = Utilities::trim(line.substr(0, rIndex));
        string second = Utilities::trim(line.substr(rIndex + 1));

        if (first.empty() || second.empty()) Utilities::error("Expected two operands to R.");

        return { "R", { Utilities::stringToInt(first), Utilities::stringToInt(second) } };
    }

    /* Given a line encoded as an explicit predicate, parses it into a ParsedLine with
     * information about the arguments.
     */
    ParsedLine parsePredicate(const string& line) {
        ParsedLine result;

        auto openIndex = line.find('(');
        if (openIndex == string::npos) Utilities::error("Couldn't find an open parenthesis in this line.");
        result.type = Utilities::trim(line.substr(0, openIndex));

        /* Find the close parenthesis that matches this open parenthesis. Make sure that it's
         * at the very end.
         */
        auto closeIndex = line.find(')', openIndex);
        if (closeIndex != line.size() - 1) Utilities::error("Extra tokens found after close parenthesis.");

        /* Split the inner part of the string to get the arguments. */
        auto strArgs = Utilities::stringSplit(string(line.begin() + openIndex + 1, line.end() - 1), ',');

        /* Trim all leading and trailing whitespace from each argument. */
        for (auto arg: strArgs) {
            result.args.push_back(Utilities::stringToInt(arg));
        }
        return result;
    }

    /* Given a line of text from a file, parses that line into a more structured
     * format. If the line can't be parsed, reports an error.
     */
    ParsedLine parse(const string& line) {
        if (line.empty()) Utilities::error("Internal error: trying to parse an empty line?");

        /* There are two possible formats here:
         *
         *    Element(n)
         *    xRy
         *
         * This means that if the first character is a number symbol, we can dive into the second
         * case, and otherwise we'll parse the first.
         */
        if (string("-+1234567890").find(line[0]) != string::npos) {
            return parseR(line);
        } else {
            return parsePredicate(line);
        }
    }

    /* Given a command to add an element to the underlying domain, adds that element
     * to the domain.
     */
    void processElement(const vector<int>& args, Relation& relation) {
        /* Confirm that there's a single argument. */
        if (args.size() != 1) Utilities::error("The Element predicate requires exactly one argument.");

        /* Insert the element. This is idempotent. */
        relation.domain.insert(args[0]);
    }

    /* Given a command to introduce a relationship between two elements, introduces that
     * relationship.
     */
    void processRelation(const vector<int>& args, Relation& relation) {
        if (args.size() != 2) Utilities::error("The xRy predicate requires exactly two arguments.");

        if (!relation.domain.count(args[0])) Utilities::error("The value " + to_string(args[0]) + " is not (yet?) in the domain.");
        if (!relation.domain.count(args[1])) Utilities::error("The value " + to_string(args[1]) + " is not (yet?) in the domain.");

        relation.r.insert({ args[0], args[1] });
    }
}

/* Given a stream that contains a definition of a group of people, parses
 * that group of people into a map from names to people. Does what might be
 * best described as pedantic error-checking.
 */
Relation loadRelation(istream& source) {
    Relation result;

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
        auto parsedLine = parse(line);

        if (parsedLine.type == "Element") {
            processElement(parsedLine.args, result);
        } else if (parsedLine.type == "R") {
            processRelation(parsedLine.args, result);
        } else {
            Utilities::error("Unknown statement type: [" + line + "]");
        }
    }

    return result;
}
