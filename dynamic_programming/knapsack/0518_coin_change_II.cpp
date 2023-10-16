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
 * ! 1 <= coins.length <= 300
 * ! 1 <= coins[i] <= 5000
 * ! All the values of coins are unique.
 * ! 0 <= amount <= 5000
 */

class Solution
{
public:
    int change(int amount, std::vector<int>& coins) { return approach2(amount, coins); }

private:
    // DP with space optimization
    int approach2(int amount, const std::vector<int>& coins)
    {
        const int n = coins.size();
        std::vector<int> dp(amount + 1, 0);
        for (int i = 1; i <= n; ++i) {
            dp[0] = 1;
            for (int j = 1; j <= amount; ++j) {
                if (j - coins[i - 1] >= 0) {
                    dp[j] = dp[j] + dp[j - coins[i - 1]];
                }
            }
        }
        return dp[amount];
    }

    // DP
    int approach1(int amount, const std::vector<int>& coins)
    {
        // dp[i][j] = num of ways to make up amount j using coins[0:i)
        // base cases:
        // - dp[0][0] = 1, only one way to make up amount 0 with an empty coin list: do nothing
        // - dp[i>0][0] = 1, only one way to make up amount 0 with a non-empty coin list
        // - dp[0][j>0] = 0, no way to make up j>0 with an empty coin list
        const int n = coins.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(amount + 1, 0));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= amount; ++j) {
                // option1: the ith coin is not used, then we make up amount j using coins[0,i-1)
                // option2: the ith coin is used, then we make up amount j-coins[i-1] using
                // coins[0:i)
                // - it is still coins[0:i) because the number of each coin is infinite
                if (j - coins[i - 1] < 0) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
                }
            }
        }
        return dp[n][amount];
    }
};
