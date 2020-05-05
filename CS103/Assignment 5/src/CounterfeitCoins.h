#ifndef CounterfeitCoins_Included
#define CounterfeitCoins_Included

#include <vector>
#include <memory>

/* Type: Coin
 *
 * A type representing a coin.
 */
using Coin = std::shared_ptr<struct RealCoin>;

/* Constant: None
 *
 * A constant representing something that isn't a coin.
 */
extern const Coin None;

/* Type: Balance
 *
 * A type representing a balance.
 */
using Balance = std::shared_ptr<struct RealBalance>;

/* Function: weigh
 *
 * Given two groups of coins and a balance, weighs those coins against one another.
 * This function returns -1 if the first group is heavier, 0 if the groups weigh
 * the same amount, and +1 if the second group is heavier.
 *
 * This function will report an error if you try to weigh two groups of unequal
 * sizes.
 */
int weigh(Balance balance, std::vector<Coin> left, std::vector<Coin> right);

/* Function: takeFrom
 *
 * Given a set of coins and a number k of coins to take, chooses and removes k of the
 * coins from the set and returns them. The input parameter is modified to have those
 * coins removed. You can use this to grab some number of coins out of the group. For
 * example, to take 137 coins out of a group, you could write something like this:
 *
 *     std::vector<Coin> coins = // ...;
 *     std::vector<Coin> some = takeFrom(coins, 137);
 *     // some now has 137 coins in it; coins now has 137 fewer coins.
 *
 * If you try to take more coins out of the bag than exist, this will trigger an error.
 */
std::vector<Coin> takeFrom(std::vector<Coin>& coins, size_t howMany);

/* You need to implement these two functions. */

/* Given 3^n coins and a balance, finds and returns the counterfeit coin from the
 * group using exactly n weighings.
 */
Coin counterfeitIn(std::vector<Coin> coins, Balance balance);

/* Given 3^n - 1 coins and a balance, finds and returns the counterfeit coin
 * from the group, if it exists, using exactly n weighings.
 */
Coin maybeCounterfeitIn(std::vector<Coin> coins, Balance balance);

#endif
