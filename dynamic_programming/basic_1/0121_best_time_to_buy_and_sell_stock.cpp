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
    int maxProfit(const std::vector<int>& prices) { return approach2(prices); }

private:
    int approach2(const std::vector<int>& prices)
    {
        // space optimization of approach 1
        if (prices.empty())
            return 0;

        int withStock = INT_MIN;
        int withoutStock = 0;
        for (const auto& price : prices) {
            withoutStock = std::max(withoutStock, withStock + price);
            withStock = std::max(withStock, -price);
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
        // - dp[0][0] = no stock, no profit
        // - dp[0][1] = no way to have a stock
        dp[0][1] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            // without stock today:
            // - without stock yesterday + do nothing today, or
            // - with stock yesterday + sell the stock today
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
            // with stock today
            // - with stock yesterday + do nothing today, or
            // - without stock yesterday + buy the stock today
            dp[i][1] = std::max(dp[i - 1][1], -prices[i - 1]);
        }
        return dp[n][0];
    }
};