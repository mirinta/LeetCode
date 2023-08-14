#include <vector>

/**
 * You are given an integer array prices where prices[i] is the price of a given stock on the ith
 * day.
 *
 * On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of
 * the stock at any time. However, you can buy it then immediately sell it on the same day.
 *
 * Find and return the maximum profit you can achieve.
 *
 * ! 1 <= prices.length <= 3 * 10^4
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
            const int backup = withStock;
            withStock = std::max(withStock, withoutStock - prices[i]);
            withoutStock = std::max(withoutStock, backup + prices[i]);
        }
        return std::max(withStock, withoutStock);
    }

    // 2D-DP, time O(N), space O(N)
    int approach1(const std::vector<int>& prices)
    {
        const int n = prices.size();
        // dp[i][0] = max profit at the end of ith day without any stock in-hand
        // dp[i][1] = max profit at the end of ith day with one stock in-had
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(2, 0));
        dp[0][1] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i - 1]);
        }
        return std::max(dp[n][0], dp[n][1]);
    }
};
