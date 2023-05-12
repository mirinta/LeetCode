#include <vector>

/**
 * You are given an integer array "coins" representing coins of different denominations and an
 * integer "amount" representing a total amount of money.
 *
 * Return the fewest number of coins that you need to make up the amount. If that amount of money
 * cannot be made up by any combination of the coins, return -1.
 *
 * You may assume that you have an infinite number of each kind of coin.
 */

class Solution
{
public:
    // approach 1: brute force
    // int coinChange(std::vector<int>& coins, int amount) {
    //     if (amount == 0)
    //         return 0;

    //     if (amount < 0)
    //         return -1;

    //     int result = INT_MAX;
    //     for (const auto& coin : coins) {
    //         const auto subproblem = coinChange(coins, amount - coin);
    //         if (subproblem < 0)
    //             continue;

    //         result = std::min(result, 1 + subproblem);
    //     }
    //     return result == INT_MAX ? -1 : result;
    // }
    // ------------------------------
    // approach 2: DP, top-down, store subproblem results
    // - table[i] = coinChange(coins, i)
    // - INT_MAX is a flag representing the subproblem is not solved
    // int coinChange(std::vector<int>& coins, int amount) {
    //     std::vector<int> table(amount + 1, INT_MAX);
    //     return dp(table, coins, amount);
    // }
    // ------------------------------
    // approach 3: DP, bottom-up
    int coinChange(std::vector<int>& coins, int amount)
    {
        const int initVal = amount + 1;
        // initialize with amount+1, because coinChange(coins, i) <= amount
        // if use INT_MAX, 1 + table[j] causes an overflow problem
        std::vector<int> table(amount + 1, initVal); // table[i] = coinChange(coins, i)
        table[0] = 0;
        // solve subproblems: f(coins, 0)->f(coins, 1)->...->f(coins, n)
        for (int i = 0; i < table.size(); ++i) {
            for (const auto& coin : coins) {
                if (i - coin < 0)
                    continue;

                table[i] = std::min(table[i], 1 + table[i - coin]);
            }
        }
        return table[amount] == initVal ? -1 : table[amount];
    }

private:
    int dp(std::vector<int>& table, const std::vector<int>& coins, int amount)
    {
        if (amount == 0)
            return 0;

        if (amount < 0)
            return -1;

        if (table[amount] != INT_MAX)
            return table[amount];

        int result = INT_MAX;
        for (const auto& coin : coins) {
            const auto subproblem = dp(table, coins, amount - coin);
            if (subproblem < 0)
                continue;

            result = std::min(result, 1 + subproblem);
        }
        table[amount] = result == INT_MAX ? -1 : result;
        return table[amount];
    }
};