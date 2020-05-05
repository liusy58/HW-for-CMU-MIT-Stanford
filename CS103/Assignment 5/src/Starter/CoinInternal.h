#ifndef CoinInternal_Included
#define CoinInternal_Included

#include "CounterfeitCoins.h"
#include <string>
#include <functional>

/* Type representing an actual coin. It just stores an index and a weight. */
struct RealCoin {
    const std::size_t index;
    const bool isCounterfeit;

    RealCoin(std::size_t i, bool counterfeit) : index(i), isCounterfeit(counterfeit) {
        // Handled by initialization list
    }
};

/* Type representing a callback function to report how a weighing is going. */
using ReportingFunction = std::function<void(std::size_t, std::vector<Coin>, std::vector<Coin>, int)>;

/* Type representing an actual balance. It's essentially all the state
 * we need to run one of these tests.
 */
struct RealBalance {
    std::size_t numWeighings = 0;

    /* Callback function to use to report progress. */
    ReportingFunction reportFn;

    explicit RealBalance(ReportingFunction fn) : reportFn(fn) {
        // Handled by initialization list
    }
};


#endif
