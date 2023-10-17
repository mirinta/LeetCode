#include <array>
#include <vector>

/**
 * You are given an array "prices" where prices[i] is the price of a given stock on the ith day.
 *
 * Find the maximum profit you can achieve. You may complete at most two transactions.
 *
 * Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock
 * before you buy again).
 *
 * ! 1 <= prices.length <= 10^5
 * ! 0 <= prices[i] <= 10^5
 */

class Solution
{
public:
    int maxProfit(std::vector<int>& prices) { return approach2(prices); }

private:
    // DP with space optimization
    int approach2(const std::vector<int>& prices)
    {
        const int n = prices.size();
        const int k = 2;
        std::vector<std::array<int, 2>> dp(1 + k, std::array<int, 2>{0, INT_MIN});
        auto prev = dp;
        for (int i = 1; i <= n; ++i) {
            prev = dp;
            for (int j = 1; j <= k; ++j) {
                dp[j][0] = std::max(prev[j][0], prev[j][1] + prices[i - 1]);
                dp[j][1] = std::max(prev[j][1], prev[j - 1][0] - prices[i - 1]);
            }
        }
        return dp[k][0];
    }

    // DP
    int approach1(const std::vector<int>& prices)
    {
        const int n = prices.size();
        const int k = 2;
        // dp[i][j][0] = max profit at the end of the ith day without holding any stock by
        // completing at most j transactions
        // dp[i][j][1] = max profit at the end of the ith day holding one stock by completing at most j
        // transactions
        // base cases: dp[0][j>=0][0] = 0, dp[0][j>=0][1] = INT_MIN
        std::vector<std::vector<std::vector<int>>> dp(
            1 + n, std::vector<std::vector<int>>(1 + k, std::vector<int>(2, 0)));
        for (int j = 0; j <= k; ++j) {
            dp[0][j][1] = INT_MIN;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                // limiting the number of transactions is equivalent to limiting the number of
                // buy-ins
                dp[i][j][0] = std::max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i - 1]);
                dp[i][j][1] = std::max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i - 1]);
            }
        }
        return dp[n][k][0];
    }
};
