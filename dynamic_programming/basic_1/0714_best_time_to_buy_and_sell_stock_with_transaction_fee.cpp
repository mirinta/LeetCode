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
    int maxProfit(std::vector<int>& prices, int fee) { return approach2(prices, fee); }

private:
    int approach2(std::vector<int>& prices, int fee)
    {
        // DP with space optimization
        const int n = prices.size();
        long withoutStock = 0;
        long withStock = INT_MIN;
        for (int i = 0; i < n; ++i) {
            const long temp = withoutStock;
            withoutStock = std::max(withoutStock, withStock + prices[i] - fee);
            withStock = std::max(withStock, temp - prices[i]);
        }
        return withoutStock;
    }

    int approach1(std::vector<int>& prices, int fee)
    {
        const int n = prices.size();
        // dp[i][0] = max profit of days[0:i) without any stock in-hand
        // dp[i][1] = max profit of days[0:i) with one stock in-hand
        std::vector<std::vector<long>> dp(n + 1, std::vector<long>(2, 0));
        dp[0][1] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1] - fee);
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i - 1]);
        }
        return dp[n][0];
    }
};
