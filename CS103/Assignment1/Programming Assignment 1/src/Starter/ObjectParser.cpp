/**
 * Code to parse a set or object. Fun fact: you'll build up the theoretical
 * machinery motivating how this parser works in Problem Set Eight!
 */
#include "ObjectParser.h"
#include "Utilities.h"
#include <queue>
#include <algorithm>
using namespace std;

namespace {
    /* Parses a single object out of a stream of tokens. */
    Object parseObject(queue<string>& tokens);

    /* Given a chunk of text out of a file, extracts up to one token from it and
     * adds it to the queue.
     */
    void extractTokensIn(const string& str, queue<string>& queue) {
        /* Clean the string. If it's nonempty, enqueue it. */
        string token = Utilities::trim(str);
        if (!token.empty()) queue.push(token);
    }
    void extractTokensIn(string::const_iterator start, string::const_iterator end,
                         queue<string>& queue) {
        extractTokensIn({ start, end }, queue);
    }

    /* Given a stream, returns the meaningful contents of that stream, which is
     * found by stripping all comments from the file and trimming each line.
     */
    string contentsOf(istream& source) {
        string result;

        for (string line; getline(source, line); ) {
            /* Trim any comments. */
            auto commentPos = line.find('#');
            if (commentPos != string::npos) {
                line.erase(line.begin() + commentPos, line.end());
            }

            /* Trim any remaining whitespace. */
            line = Utilities::trim(line);

            /* If the line is blank, ignore it. */
            if (line.empty()) continue;

            /* Append the line, plus a space character (so that multiline strings are treated
             * as though each individual term is space-separated).
             */
            result += line;
            result += ' ';
        }

        return result;
    }

    /* Given a stream, returns a sequence of tokens from that stream. Tokens
     * are either individual names of things, commas, or braces.
     */
    queue<string> tokenize(istream& source) {
        string contents = contentsOf(source);

        queue<string> result;

        /* Starting at zero, keep scanning for a meaningful character and
         * deciding how to handle it.
         */
        size_t start = 0;
        do {
            /* Search for the next meaningful character. */
            size_t sepPos = contents.find_first_of("{,}", start);

            /* If we don't find one, grab the rest of the string and process it. */
            if (sepPos == string::npos) {
                extractTokensIn(contents.begin() + start, contents.end(), result);
                break;
            }

            /* If we did find one, grab everything up to it as a token, then treat it
             * as a token.
             */
            extractTokensIn(contents.begin() + start, contents.begin() + sepPos, result);
            result.push(string() + contents[sepPos]);
            start = sepPos + 1;

        } while (start != contents.size());

        return result;
    }

    /* Dequeues and returns an element from a queue. */
    string dequeueFrom(queue<string>& tokens) {
        if (tokens.empty()) {
            Utilities::error("Unexpected end of input found.");
        }
        string result = tokens.front();
        tokens.pop();
        return result;
    }

    /* Peeks at the top of the queue. */
    string peekAt(queue<string>& tokens) {
        if (tokens.empty()) {
            Utilities::error("Unexpected end of input found.");
        }
        return tokens.front();
    }

    /* Pulls a single token from the queue, reporting an error if what was found didn't
     * match what was expected.
     */
    void expect(const string& expected, queue<string>& tokens) {
        if (tokens.empty()) {
            Utilities::error("Expected '" + expected + "', but found the end of the input.");
        }

        auto token = dequeueFrom(tokens);
        if (token != expected) {
            Utilities::error("Expected '" + expected + "', but found '" + token + "'.");
        }
    }

    /* Given a token stream, parses a single set out of the stream, reporting an error if
     * it's not possible.
     */
    Object parseSet(queue<string>& tokens) {
        /* Grab the first token, which must be an opening brace. */
        expect("{", tokens);

        /* If we see a close brace, it means that we have the empty set. */
        if (peekAt(tokens) == "}") {
            tokens.pop();
            return { make_shared<ActualSet>() };
        }

        /* Otherwise, we have an argument list to read. So let's go do that! */
        set<Object> elements;
        while (true) {
            elements.insert(parseObject(tokens));

            /* If we see a close brace, we're done. */
            if (peekAt(tokens) == "}") {
                tokens.pop();
                return { make_shared<ActualSet>(elements) };
            }

            /* Otherwise, we should see a comma. */
            expect(",", tokens);
        }
    }

    /* Given a token stream pointing at an identifier, parses it into an
     * Object. The name "Thing" is less than ideal and refers to a non-set
     * object.
     */
    Object parseThing(queue<string>& tokens) {
        string token = dequeueFrom(tokens);
        if (token == "{" || token == "}" || token == ",") {
            Utilities::error("Expected an object, but found '" + token + "' instead.");
        }
        return { make_shared<ActualObject>(token) };
    }

    /* Given a token stream, parses an object from it. */
    Object parseObject(queue<string>& tokens) {
        /* If the first token is an open brace, read a set. */
        if (peekAt(tokens) == "{") {
            return parseSet(tokens);
        } else {
            return parseThing(tokens);
        }
    }

    /* Given a token stream, parses it into an object or reports an error in doing so. */
    Object parseSingleObject(queue<string>& tokens) {
        /* Grab a single object from it. */
        auto result = parseObject(tokens);

        if (!tokens.empty()) {
            Utilities::error("Unexpected contents found after end of object: [" + dequeueFrom(tokens) + "]");
        }
        return result;
    }
}

/* Given a stream that contains a definition of a group of people, parses
 * that group of people into a map from names to people. Does what might be
 * best described as pedantic error-checking.
 */
Object loadObject(istream& source) {
    queue<string> tokens = tokenize(source);
    return parseSingleObject(tokens);
}
