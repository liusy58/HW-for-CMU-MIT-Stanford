#include "TestDriver.h"
#include <memory>
#include <vector>
using namespace std;

namespace {
    /* Runs a single test and reports the result. */
    NamedResult runTest(const NamedTest& test,
                        function<Coin(vector<Coin>, Balance)> fn,
                        ReportingFunction reportingFn) {
        /* Create enough coins to go around. */
        vector<Coin> coins;
        coins.reserve(test.numCoins);

        for (int i = 0; size_t(i) < test.numCoins; i++) {
            coins.emplace_back(make_shared<RealCoin>(size_t(i), i == test.counterfeitIndex));
        }

        /* Set up an empty balance. */
        Balance b = make_shared<RealBalance>(reportingFn);

        /* Run the test! */
        try {
            Coin result = fn(coins, b);

            /* If the wrong number of weighings happened, something is wrong. */
            if (b->numWeighings != test.numWeighings) {
                return { test.name, Result::FAIL,
                         "Wrong number of weighings; expected " + to_string(test.numWeighings) + ", made " + to_string(b->numWeighings) + ".",
                         result
                };
            }

            /* If there's a counterfeit, see whether we found it. */
            if (test.counterfeitIndex != -1) {
                if (result == None) {
                    return {
                        test.name,
                        Result::FAIL,
                        "You reported no coins were counterfeit, but there was a counterfeit!",
                        result
                    };
                }
                if (int(result->index) != test.counterfeitIndex) {
                    return {
                        test.name,
                        Result::FAIL,
                        "The coin you returned was not counterfeit!",
                        result
                    };
                }
                return {
                    test.name,
                    Result::PASS,
                    "Correct!",
                    result
                };
            }
            /* Otherwise, if there's no counterfeit, make sure we returned none! !*/
            else {
                if (result != None) {
                    return {
                        test.name,
                        Result::FAIL,
                        "You reported that a counterfeit exists, but all coins are genuine!",
                        result
                    };
                }
                return {
                    test.name,
                    Result::PASS,
                    "Correct!",
                    result
                };
            }
        } catch (const exception& e) {
            return { test.name, Result::ERROR, e.what(), None };
        }
    }
}

std::vector<NamedResult> runAllTests(const vector<NamedTest>& tests,
                                     function<Coin(vector<Coin>, Balance)> fn,
                                     ReportingFunction reportingFn) {
    vector<NamedResult> result;
    for (auto test: tests) {
        result.emplace_back(runTest(test, fn, reportingFn));
    }
    return result;
}
