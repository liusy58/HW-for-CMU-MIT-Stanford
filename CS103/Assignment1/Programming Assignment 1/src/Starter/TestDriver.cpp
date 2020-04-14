#include "TestDriver.h"
#include "ObjectParser.h"
#include <functional>
#include <vector>
using namespace std;

namespace {
    /* Runs a single test and reports the result. */
    TestResults runTest(const string& sName,
                        const string& tName,
                        istream& sInput, istream& tInput,
                        const vector<NamedFunction>& tests) {
        /* We trust that the objects here are well-formed, so there's no need
         * to try-catch for exceptions that might be generated.
         *
         * That being said, our internal autograder is written way more defensively
         * than this. :-)
         */
        auto S = loadObject(sInput);
        auto T = loadObject(tInput);

        vector<NamedResult> results;

        /* Run all the tests and report the result. */
        for (const auto& test: tests) {
            try {
                results.push_back({ test.name, test.testFunction(S, T)? Result::TRUE : Result::FALSE, "" });
            } catch (const exception& e) {
                results.push_back({ test.name, Result::ERROR, e.what() });
            } catch (...) {
                results.push_back({ test.name, Result::ERROR, "An unknown error occurred." });
            }
        }
        
        /* Clear and rewind the stream so that we can reuse it. We could use the
         * filelib.h header, but this file is designed to work without the
         * Stanford C++ Libraries and therefore doesn't rely on any features
         * provided by it.
         */
        sInput.clear();
        sInput.seekg(0);

        tInput.clear();
        tInput.seekg(0);

        return { sName, tName, results };
    }
}

vector<TestResults> runAllTests(const vector<NamedSource>& sources,
                                const vector<NamedFunction>& tests) {
    vector<TestResults> result;
    for (auto& source: sources) {
        result.emplace_back(runTest(source.sName, source.tName, *source.sSource, *source.tSource, tests));
    }
    return result;
}
