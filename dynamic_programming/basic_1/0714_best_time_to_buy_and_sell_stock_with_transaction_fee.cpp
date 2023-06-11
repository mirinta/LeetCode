#include <vector>

/**
 * You are given an array prices where prices[i] is the price of a given stock on the ith day, and
 * an integer fee representing a transaction fee.
 *
 * Find the maximum profit you can achieve. You may complete as many transactions as you like, but
 * you need to pay the transaction fee for each transaction.
 *
 * Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock
 * before you buy again).
 *
 * ! 1 <= prices.length <= 5 * 10^4
 * ! 1 <= prices[i] < 5 * 10^4
 * ! 0 <= fee < 5 * 10^4
 */

class Solution
{
public:
    int maxProfit(const std::vector<int>& prices, int fee) { return approach2(prices, fee); }

private:
    int approach2(const std::vector<int>& prices, int fee)
    {
        // space optimization of approach1
        if (prices.empty())
            return 0;

        long withStock = INT_MIN;
        long withoutStock = 0;
        for (const auto& price : prices) {
            long backup = withoutStock;
            withoutStock = std::max(withoutStock, withStock + price - fee);
            withStock = std::max(withStock, backup - price);
        }
        return withoutStock;
    }

    int approach1(const std::vector<int>& prices, int fee)
    {
        if (prices.empty())
            return 0;

        // dp[i][0] = max profit of days[0:i) without stock on the ith day
        // dp[i][1] = max profit of days[0:i) with stock on the ith day
        const auto n = prices.size();
        std::vector<std::vector<long>> dp(n + 1, std::vector<long>(2, 0));
        dp[0][1] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1] - fee);
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i - 1]);
        }
        return dp[n][0];
    }
};