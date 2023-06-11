#include <vector>

/**
 * You are given an integer array "coins" representing coins of different denominations and an
 * integer "amount" representing a total amount of money.
 *
 * Return the number of combinations that make up that amount. If that amount of money cannot be
 * made up by any combination of the coins, return 0;
 *
 * You may assume that you have an infinite number of each kind of coin.
 *
 * The answer is guaranteed to fit into a signed 32-bit integer.
 *
 * Example:
 * Input: amount = 5, coins = [1, 2, 5]
 * Output: 4
 * Explanation: there are four ways to make the amount:
 * 5 = 5
 * 5 = 2 + 2 + 1
 * 5 = 2 + 1 + 1 + 1
 * 5 = 1 + 1 + 1 + 1
 */

class Solution
{
public:
    int change(int amount, std::vector<int>& coins)
    {
        // consider it as a knapsack problem:
        // how many ways to fill a knapsack of capacity M with N packages?
        // - each package has a value representing the capacity it occupies
        // dp[i][j] = number of ways that make up amount j with coins[0:i)
        const auto n = coins.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(amount + 1, 0));
        // base case:
        // - dp[i][0] = 1, there's only one way to make up 0 amount: choose nothing
        // - for any j != 0, dp[0][j] = 0 coin list is empty, no way to make up the target amount
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= amount; ++j) {
                if (j - coins[i - 1] < 0) {
                    // denomination of ith coin is larger than j,
                    // we should still use the previous i-1 coins to make up j
                    dp[i][j] = dp[i - 1][j];
                } else {
                    // here, we can either pick or not pick the ith coin
                    // - if the ith coin is picked, then the coin range is expanded to [0:i),
                    //   because each coin can be used multiple times
                    //   our goal is to make up the remaining amount r = j - denomination of the ith
                    //   coin, we have dp[i][r] ways to achieve the goal
                    // - otherwise, the coin list is still [0:i-1), and the goal is still j,
                    //   we have d[i-1][j] ways to achieve the goal
                    // in summary, for the ith coin, we have d[i-1][j] + dp[i][r] ways to make up j
                    dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
                }
            }
        }
        return dp[n][amount];
    }
};