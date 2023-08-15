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
    // 1D-DP, time O(AN), space O(A)
    // A is the amount, and N is the number of coins
    int approach2(int amount, const std::vector<int>& coins)
    {
        const int n = coins.size();
        std::vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= amount; ++j) {
                if (j >= coins[i - 1]) {
                    dp[j] += dp[j - coins[i - 1]];
                }
            }
        }
        return dp[amount];
    }

    // 2D-DP, time O(AN), space O(AN)
    // A is the amount, and N is the number of coins
    int approach1(int amount, const std::vector<int>& coins)
    {
        const int n = coins.size();
        // dp[i][j] = num of combinations to make up amount i using coins[0:i)
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(amount + 1, 0));
        // base cases:
        // - dp[0][0] = 1, only one way to make up zero amount with empty coin list: choose nothing
        // - dp[i][0] = 1, same as above
        // - dp[0][j] = 0, no way to make up non-zero amount with an empty coin list
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= amount; ++j) {
                // case1: the ith coin is not used
                dp[i][j] = dp[i - 1][j];
                // case2: the ith coin is used
                if (j >= coins[i - 1]) {
                    // not dp[i][j] += dp[i-1][j-coins[i-1]],
                    // because the number of each coin is infinite,
                    // we can still use the ith coin to make up the remaining amount
                    dp[i][j] += dp[i][j - coins[i - 1]];
                }
            }
        }
        return dp[n][amount];
    }
};