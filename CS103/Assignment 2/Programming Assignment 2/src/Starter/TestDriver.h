/**
 * File: TestDriver.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * Logic to run a series of tests on a given collection of sources. This is abstracted away from
 * the rest of the program so that we can swap out the main function between the student version
 * of the code (which visualizes the results) and the autograder (which dumps the results into a
 * file).
 *
 * Note that the logic to list all the test cases is not included here, since we rely on the
 * Stanford C++ Libraries for this on the student side and we factor those libraries out for
 * autograding.
 */

#ifndef TestDriver_Included
#define TestDriver_Included

#include "TestingTypes.h"
#include <istream>
#include <vector>
#include <memory>
#include <functional>

/* Type: NamedSource
 *
 * A pairing of a name for an istream and an actual istream.
 */
struct NamedSource {
    std::string name;
    std::shared_ptr<std::istream> source;
};

/* A struct representing a test function to run along with the name of that
 * function.
 */
struct NamedFunction {
    std::function<bool(std::set<Person>)> testFunction;
    std::string name;
};

/* Given a collection of named sources, runs all of the tests specified in those sources
 * and returns a vector of the results of the tests. The input streams will all be rewound
 * to their original starting point and cleared so that the tests can be reused.
 */
std::vector<TestResults> runAllTests(const std::vector<NamedSource>& sources,
                                     const std::vector<NamedFunction>& tests);

#endif
