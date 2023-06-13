#include <vector>

/**
 * There are n piles of coins on a table. Each pile consists of a positive number of coins of
 * assorted denominations.
 *
 * In one move, you can choose any coin on top of any pile, remove it, and add it to your wallet.
 *
 * Given a list piles, where piles[i] is a list of integers denoting the composition of the ith pile
 * from top to bottom, and a positive integer k, return the maximum total value of coins you can
 * have in your wallet if you choose exactly k coins optimally.
 *
 * ! n == piles.length
 * ! 1 <= n <= 1000
 * ! 1 <= piles[i][j] <= 10^5
 * ! 1 <= k <= sum(piles[i].length) <= 2000
 */

class Solution
{
public:
    int maxValueOfCoins(const std::vector<std::vector<int>>& piles, int k)
    {
        const auto n = piles.size();
        std::vector<std::vector<int>> preSum(n);
        for (size_t i = 0; i < n; ++i) {
            preSum[i].reserve(piles[i].size() + 1);
            preSum[i].push_back(0);
            int sum = 0;
            for (const auto& val : piles[i]) {
                sum += val;
                preSum[i].push_back(sum);
            }
        }
        // dp[i][j] = max value of choosing j coins from piles[0:i)
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
        for (size_t i = 1; i <= n; ++i) {
            for (size_t j = 1; j <= k; ++j) {
                for (size_t t = 0; t <= std::min(j, piles[i - 1].size()); ++t) {
                    // pick t coins from the ith pile:
                    dp[i][j] = std::max(dp[i][j], dp[i - 1][j - t] + preSum[i - 1][t]);
                }
            }
        }
        return dp[n][k];
    }
};