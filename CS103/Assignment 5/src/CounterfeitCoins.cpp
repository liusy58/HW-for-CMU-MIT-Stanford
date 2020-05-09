#include "CounterfeitCoins.h"
#include <stdexcept>
#include<iostream>
/* A helpful function you might want to use in the course of solving this problem. */
namespace { // Keep this function private to this file.
    bool isPowerOfThree(size_t n) {
        /* Base case: 1 is a power of three. */
        if (n == 1) return true;

        /* Recursive case: n is a power of three iff it's a multiple of three and
         * n / 3 is a multiple of three.
         */
        return (n % 3 == 0) && isPowerOfThree(n / 3);
    }
}


/* Given 3^n coins and a balance, finds and returns the counterfeit coin from the
 * group using exactly n weighings.
 *
 * We will only test your code on inputs of size 3^n and you don't need to worry
 * about other sizes of inputs. However, we recommend leaving in the check at the
 * top of this function to make debugging easier in the event that you accidentally
 * make a recursive call of the wrong size.
 */
Coin counterfeitIn(std::vector<Coin> coins, Balance balance) {
    /* Helpful little check to make sure each recursive call is given the right number
     * of coins. You can delete this if you'd like, but we'd recommend against it. :-)
     */
    if (!isPowerOfThree(coins.size())) {
        throw std::invalid_argument("Input number of coins must be a power of three.");
    }
    if(coins.size()==1)
        return coins[0];
    int len=(int)coins.size()/3;
    std::vector<Coin> pack1 = takeFrom(coins, len);
    std::vector<Coin> pack2 = takeFrom(coins, len);
    std::vector<Coin> pack3 = takeFrom(coins, len);
    int res=weigh(balance,pack1,pack2);
    if(res==-1)
        return counterfeitIn(pack1,balance);
    else if(res==1)
        return counterfeitIn(pack2,balance);
    return counterfeitIn(pack3,balance);
}

/* Given 3^n - 1 coins and a balance, finds and returns the counterfeit coin
 * from the group, if it exists, using exactly n weighings. If the counterfeit
 * doesn't exist, your code should return the constant None.
 *
 * We will only test your code on inputs of size 3^n-1 and you don't need to worry
 * about other sizes of inputs. However, we recommend leaving in the check at the
 * top of this function to make debugging easier in the event that you accidentally
 * make a recursive call of the wrong size.
 */
Coin maybeCounterfeitIn(std::vector<Coin> coins, Balance balance) {
    /* Helpful little check to make sure each recursive call is given the right number
     * of coins. You can delete this if you'd like, but we'd recommend against it. :-)
     */
    std::cout<<coins.size()<<std::endl;
//    if (!isPowerOfThree(coins.size() + 1)) {
//        throw std::invalid_argument("Input number of coins must be one less than a power of three.");
//    }

    if(coins.size()==2)
    {
        std::vector<Coin> pack1 = takeFrom(coins, 1);
        std::vector<Coin> pack2 = takeFrom(coins, 1);
        int res=weigh(balance,pack1,pack2);
        if(res==-1)
            return pack1[0];
        if(res==1)
            return pack2[0];
        return None;
    }
    if(coins.size()==3)
    {
        std::vector<Coin> pack1 = takeFrom(coins, 1);
        std::vector<Coin> pack2 = takeFrom(coins, 1);
        std::vector<Coin> pack3 = takeFrom(coins, 1);
        int res=weigh(balance,pack1,pack2);
        if(res==-1)
            return pack1[0];
        if(res==1)
            return pack2[0];
        res=weigh(balance,pack1,pack3);
        if(res==-1)
            return pack1[0];
        if(res==1)
            return pack2[0];
        return None;
    }
    int len=(int)(coins.size()+1)/3;
    std::cout<<" !!!"<<len<<std::endl;


    std::vector<Coin> pack1 = takeFrom(coins, len);
    std::vector<Coin> pack2 = takeFrom(coins, len);


    int res=weigh(balance,pack1,pack2);
    if(!res)
        return  maybeCounterfeitIn(coins,balance);
    else if(res==-1)
        return maybeCounterfeitIn(pack1,balance);
    return maybeCounterfeitIn(pack2,balance);

}
