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
#include "CoinInternal.h"
#include <vector>
#include <functional>

/* Type: NamedTest
 *
 * A pairing of a name for a test and an actual test case.
 */
struct NamedTest {
    std::string name;
    std::size_t numCoins;
    std::size_t numWeighings;
    int counterfeitIndex; // -1 for not present
};

/* Given a collection of named tests, runs all of the tests specified in those sources
 * and returns a vector of the results of the tests.
 */
std::vector<NamedResult> runAllTests(const std::vector<NamedTest>& tests,
                                     std::function<Coin(std::vector<Coin>, Balance)> fn,
                                     ReportingFunction reportFn);

#endif
