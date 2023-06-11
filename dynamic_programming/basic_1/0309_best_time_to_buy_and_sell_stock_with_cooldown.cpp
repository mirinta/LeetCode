#include <vector>

/**
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
 *
 * Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e.,
 * buy one and sell one share of the stock multiple times) with the following restrictions:
 *
 * - After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
 *
 * Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock
 * before you buy again).
 *
 * ! 1 <= prices.length <= 5000
 * ! 0 <= prices[i] <= 1000
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

        int withStock = INT_MIN;
        int withoutStock = 0;
        int withoutStockPrev = 0;
        for (const auto& price : prices) {
            int backup = withoutStock;
            withoutStock = std::max(withoutStock, withStock + price);
            withStock = std::max(withStock, withoutStockPrev - price);
            withoutStockPrev = backup;
        }
        return withoutStock;
    }
    int approach1(const std::vector<int>& prices)
    {
        if (prices.empty())
            return 0;

        // dp[i][0] = max profit of days[0:i) without stock on the ith day
        // dp[i][1] = max profit of days[0:i) with stock on the ith day
        const auto n = prices.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(2, 0));
        // base cases:
        // - dp[0][0] = 0 = dp[1][0], no stock, no profit
        // - dp[0][1] = -1, no way to have a stock at this day
        // - dp[1][1] = -prices[0], buy stock on the first day
        dp[0][1] = -1;
        dp[1][1] = -prices[0];
        for (int i = 2; i <= n; ++i) {
            // this day without stock:
            // - yesterday without stock, or
            // - yesterday with stock and sell stock on this day
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
            // this day with stock:
            // - yesterday with stock, or
            // - the day before yesterday without stock and buy stock on this day
            //   because there one day cool down between each transaction
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 2][0] - prices[i - 1]);
        }
        return dp[n][0];
    }
};