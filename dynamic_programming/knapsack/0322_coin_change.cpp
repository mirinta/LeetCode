#include <vector>

/**
 * You are given an integer array coins representing coins of different denominations and an integer
 * amount representing a total amount of money.
 *
 * Return the fewest number of coins that you need to make up that amount. If that amount of money
 * cannot be made up by any combination of the coins, return -1.
 *
 * You may assume that you have an infinite number of each kind of coin.
 *
 * ! 1 <= coins.length <= 12
 * ! 1 <= coins[i] <= 2^31 - 1
 * ! 0 <= amount <= 10^4
 */

class Solution
{
public:
    int coinChange(std::vector<int>& coins, int amount) { return approach2(coins, amount); }

private:
    // DP with space optimization, TC = O(NM), SC = O(M)
    int approach2(const std::vector<int>& coins, int amount)
    {
        const int n = coins.size();
        std::vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= amount; ++j) {
                if (coins[i - 1] > j || dp[j - coins[i - 1]] == INT_MAX)
                    continue;

                dp[j] = std::min(dp[j], dp[j - coins[i - 1]] + 1);
            }
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }

    // DP, TC = O(NM), SC = O(NM)
    int approach1(const std::vector<int>& coins, int amount)
    {
        // dp[i][j] = min num of coins to make up j using coins[0:i-1]
        const int n = coins.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(amount + 1, INT_MAX));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= amount; ++j) {
                if (coins[i - 1] > j || dp[i][j - coins[i - 1]] == INT_MAX) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = std::min(dp[i - 1][j], dp[i][j - coins[i - 1]] + 1);
                }
            }
        }
        return dp[n][amount] == INT_MAX ? -1 : dp[n][amount];
    }
};
