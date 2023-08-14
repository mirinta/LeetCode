#include <vector>

/**
 * You are given an array "prices" where prices[i] is the price of a given stock on the ith day.
 *
 * You want to maximize your profit by choosing a single day to buy one stock and choosing in a
 * different day in teh future to sell that stock.
 *
 * Return the maximum profit you can achieve from this transaction. If you cannot achieve any
 * profit, return 0.
 *
 * ! 1 <= prices.length <= 10^5
 * ! 0 <= prices[i] <= 10^4
 */

class Solution
{
public:
    int maxProfit(std::vector<int>& prices) { return approach2(prices); }

private:
    // 1D-DP, time O(N), space O(1)
    int approach2(const std::vector<int>& prices)
    {
        const int n = prices.size();
        int withStock = INT_MIN;
        int withoutStock = 0;
        for (int i = 0; i < n; ++i) {
            withoutStock = std::max(withoutStock, withStock + prices[i]);
            withStock = std::max(withStock, -prices[i]);
        }
        return withoutStock;
    }

    // 2D-DP, time O(N), space O(N)
    int approach1(const std::vector<int>& prices)
    {
        const int n = prices.size();
        // dp[i][0] = max profit at the end of ith day without any stock in-hand
        // dp[i][1] = max profit at the end of ith day with one stock in-hand
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(2, 0));
        dp[0][1] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
            dp[i][1] = std::max(dp[i - 1][1], -prices[i - 1]);
        }
        return dp[n][0];
    }
};
