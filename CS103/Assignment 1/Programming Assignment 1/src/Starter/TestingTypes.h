/**
 * File: TestingTypes.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * Types used for reporting results of tests run on sets.
 */
#ifndef TestingTypes_Included
#define TestingTypes_Included

#include "SetInternal.h"
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
    std::string message; // Optional
};

/* Type: TestCase
 *
 * Information about a test case and how it went.
 */
struct TestResults {
    std::string sName;
    std::string tName;
    std::vector<NamedResult> results;
};

#endif
