#include <vector>

/**
 * You are given an integer array prices where prices[i] is the price of a given stock on the ith
 * day, and an integer k.
 *
 * Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may
 * buy at most k times and sell at most k times.
 *
 * Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock
 * before you buy again).
 *
 * ! 1 <= k <= 100
 * ! 1 <= prices.length <= 1000
 * ! 0 <= prices[i] <= 1000
 */

class Solution
{
public:
    int maxProfit(int k, const std::vector<int>& prices)
    {
        if (k <= 0 || prices.empty())
            return 0;

        // dp[i][j][0] = max profit of days[0:i) with j buy-in's and without stock on the ith day
        // dp[i][j][1] = max profit of days[0:i) with j buy-in's and with stock on the ith day
        // NOTE:
        // Each transaction starts with a buy-in and ends with a sell-out.
        // Therefore, limiting the number of transactions is equivalent to limiting the number of
        // buy-in actions.
        const auto n = prices.size();
        std::vector<std::vector<std::vector<int>>> dp(
            n + 1, std::vector<std::vector<int>>(k + 1, std::vector<int>(2, 0)));
        for (int j = 0; j <= k; ++j) {
            dp[0][j][1] = INT_MIN;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                dp[i][j][0] = std::max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i - 1]);
                dp[i][j][1] = std::max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i - 1]);
            }
        }
        return dp[n][k][0];
    }
};