#include "TestDriver.h"
#include "RelationParser.h"
#include <functional>
#include <vector>
#include <iostream>
using namespace std;

namespace {
    /* Runs a single test and reports the result. */
    TestResults runTest(const string& filename, istream& input,
                        const vector<NamedFunction>& tests) {
        Relation relation;
        try {
            relation = loadRelation(input);
        } catch (const exception& e) {
            cerr << "An error occurred loading the file '" << filename << "'." << endl;
            cerr << "Error: " << e.what() << endl;
            throw e;
        }

        vector<NamedResult> results;

        /* Run all the tests and report the result. */
        for (const auto& test: tests) {
            try {
                results.push_back({ test.name, test.testFunction(relation)? Result::TRUE : Result::FALSE });
            } catch (...) {
                results.push_back({ test.name, Result::ERROR });
            }
        }
        
        /* Clear and rewind the stream so that we can reuse it. */
        input.clear();
        input.seekg(0);

        return { filename, results, relation };
    }
}

vector<TestResults> runAllTests(const vector<NamedSource>& sources,
                                const vector<NamedFunction>& tests) {
    vector<TestResults> result;
    for (auto& source: sources) {
        result.emplace_back(runTest(source.name, *source.source, tests));
    }
    return result;
}
