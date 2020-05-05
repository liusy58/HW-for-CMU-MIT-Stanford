/**
 * File: TestingTypes.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * Types used for reporting results of tests run on groups of people.
 */
#ifndef TestingTypes_Included
#define TestingTypes_Included

#include <string>
#include <vector>

#include "CoinInternal.h"

/* Type: Result
 *
 * Enumerated type representing the result of a test.
 */
enum class Result {
    FAIL,
    PASS,
    ERROR
};

/* Type: NamedResult
 *
 * A type representing a single test result.
 */
struct NamedResult {
    std::string name;
    Result result;
    std::string message;
    Coin coin;
};

#endif
