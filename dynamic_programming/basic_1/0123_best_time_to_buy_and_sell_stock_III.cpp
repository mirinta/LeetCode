#include <vector>

/**
 * You are given an array "prices" where prices[i] is the price of a given stock on the ith day.
 *
 * Find the maximum profit you can achieve. You may complete at most two transactions.
 *
 * Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock
 * before you buy again).
 */

class Solution
{
public:
    int maxProfit(const std::vector<int>& prices)
    {
        if (prices.empty())
            return 0;

        // dp[i][k][0] = max profit of days[0:i) with k buy-in's and without stock on the ith day
        // dp[i][k][1] = max profit of days[0:i) with k buy-in's and wit stock on the ith day
        // NOTE:
        // Each transaction starts with a buy-in and ends with a sell-out.
        // Therefore, limiting the number of transactions is equivalent to limiting the number of
        // buy-in actions.
        const auto n = prices.size();
        const auto maxTransactions = 2;
        std::vector<std::vector<std::vector<int>>> dp(
            n + 1, std::vector<std::vector<int>>(maxTransactions + 1, std::vector<int>(2, 0)));
        for (int k = 0; k <= maxTransactions; ++k) {
            dp[0][k][1] = INT_MIN;
        }
        for (int i = 1; i <= n; ++i) {
            for (int k = 1; k <= maxTransactions; ++k) {
                dp[i][k][0] = std::max(dp[i - 1][k][0], dp[i - 1][k][1] + prices[i - 1]);
                dp[i][k][1] = std::max(dp[i - 1][k][1], dp[i - 1][k - 1][0] - prices[i - 1]);
            }
        }
        return dp[n][maxTransactions][0];
    }
};