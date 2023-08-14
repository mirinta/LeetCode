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
    int maxProfit(int k, std::vector<int>& prices) { return approach2(k, prices); }

private:
    // DP with space optimization, time O(NK), space O(K)
    int approach2(int k, const std::vector<int>& prices)
    {
        const int n = prices.size();
        std::vector<std::vector<int>> dp(k + 1, std::vector<int>(2, 0));
        for (int j = 0; j <= k; ++j) {
            dp[j][1] = INT_MIN;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= k; ++j) {
                dp[j][0] = std::max(dp[j][0], dp[j][1] + prices[i]);
                dp[j][1] = std::max(dp[j][1], dp[j - 1][0] - prices[i]);
            }
        }
        return std::max(dp[k][0], dp[k][1]);
    }

    // DP, time O(NK), space O(NK)
    int approach1(int k, const std::vector<int>& prices)
    {
        const int n = prices.size();
        // each transaction starts with a buy-in and ends with a sell-out,
        // so limiting the num of transactions is equivalent to limiting the num of buy-in's
        // dp[i][j][0] = max profit at the end of ith day without any stock in hand, and with at
        // most j buy-in's dp[i][j][1] = max profit at the end of ith day with one stock in hand,
        // and with at most j buy-in's
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
        return std::max(dp[n][k][0], dp[n][k][1]);
    }
};
