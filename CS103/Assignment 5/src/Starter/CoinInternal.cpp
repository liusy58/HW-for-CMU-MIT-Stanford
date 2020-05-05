#include "CoinInternal.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
using namespace std;

/* Static singleton representing no coin. */
const Coin None;

/* Function: weigh
 *
 * Given two groups of coins and a balance, weighs those coins against one another.
 * This function returns -1 if the first group is heavier, 0 if the groups weigh
 * the same amount, and +1 if the second group is heavier.
 *
 * This function will report an error if you try to weigh two groups of unequal
 * sizes.
 */
int weigh(Balance balance, vector<Coin> left, vector<Coin> right) {
    /* Confirm the two sides have the same number of coins. */
    if (left.size() != right.size()) {
        throw std::invalid_argument("The two sets of coins given to the balance must have the same size.");
    }

    /* Increment the number of weighings so we can see whether the right quantity
     * were made.
     */
    balance->numWeighings++;

    /* Actually do the comparison. */
    int result = 0;
    if (any_of(left.begin(),  left.end(),  [] (Coin c) { return c->isCounterfeit; })) result = -1;
    if (any_of(right.begin(), right.end(), [] (Coin c) { return c->isCounterfeit; })) result = +1;

    balance->reportFn(balance->numWeighings, left, right, result);
    return result;
}

/* takeFrom just rips coins off the front of the vector. No, that's not very efficient.
 * But it makes the output more predictable.
 */
std::vector<Coin> takeFrom(std::vector<Coin>& coins, size_t howMany) {
    /* You can't take something from nothing! */
    if (howMany > coins.size()) {
        throw std::invalid_argument("Cannot take " + to_string(howMany) + " coin" + (howMany == 1? string(""): string("s")) +
                                    " from a collection of " + to_string(coins.size()) + "!");
    }

    /* Determine the range of coins to transfer. */
    auto end = std::next(coins.begin(), howMany);

    /* Transfer those coins over. */
    std::vector<Coin> result(coins.begin(), end);

    /* Remove them from the original set. */
    coins.erase(coins.begin(), end);

    return result;
}
