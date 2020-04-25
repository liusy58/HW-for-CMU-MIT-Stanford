/**
 * File: TestingTypes.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * Types used for reporting results of tests run on groups of people.
 */
#ifndef TestingTypes_Included
#define TestingTypes_Included

#include "LogicInternal.h"
#include <string>
#include <vector>

/* Type: Result
 *
 * Enumerated type representing the result of a test.
 */
enum class Result {
    FALSE,
    TRUE,
    ERROR
};

/* Type: NamedResult
 *
 * A type representing a single test result.
 */
struct NamedResult {
    std::string name;
    Result result;
};

/* Type: TestCase
 *
 * Information about a test case and how it went.
 */
struct TestResults {
    std::string name;
    std::vector<NamedResult> results;
    Group group;
};

#endif
