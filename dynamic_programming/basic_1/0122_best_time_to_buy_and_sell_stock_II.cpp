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
    int maxProfit(const std::vector<int>& prices) { return approach2(prices); }

private:
    int approach2(const std::vector<int>& prices)
    {
        // space optimization of approach1
        if (prices.empty())
            return 0;

        const auto n = prices.size();
        int withStock = INT_MIN;
        int withoutStock = 0;
        for (const auto& price : prices) {
            int backupWithoutStock = withoutStock;
            withoutStock = std::max(withoutStock, withStock + price);
            withStock = std::max(withStock, backupWithoutStock - price);
        }
        return withoutStock;
    }

    int approach1(const std::vector<int>& prices)
    {
        if (prices.empty())
            return 0;

        // dp[i][0] = max profit of days[0:i) without stock on the ith day
        // dp[i][j] = max profit of days[0:i) with stock on the ith day
        const auto n = prices.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(2, 0));
        dp[0][1] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            // buy and sell stock on the same day, profit = 0
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i - 1]);
        }
        return dp[n][0];
    }
};