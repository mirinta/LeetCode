#include <vector>

/**
 * There are a row of "n" houses, each house can be painted with one of the "k" colors. The cost of
 * painting each house with a certain color is different. You have to paint all the houses such that
 * no two adjacent houses have the same color.
 *
 * The cost of painting each house with a certain color is represented by an "n x k" cost matrix
 * costs.
 *
 * - For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost
 * of painting house 1 with color 2, and so on...
 *
 * Return the minimum cost to paint all houses.
 *
 * ! Could you solve it in O(nk) runtime?
 */

class Solution
{
public:
    // time O(n * k^2), space O(n * k)
    int minCostII(std::vector<std::vector<int>>& costs)
    {
        if (costs.empty())
            return 0;

        const auto n = costs.size();
        const auto k = costs[0].size();
        // dp[i][j] = minCost of painting house[0:i] and house[i] is painted with color[j]
        // since we can't use the same color to paint two adjacent houses,
        // then dp[i][j] = costs[i][j] + min(dp[i-1][p], for all p != j),
        // where costs[i][j] is the cost of painting house i with color j
        // the final result is the min value of the last row of dp
        std::vector<std::vector<int>> dp(n, std::vector<int>(k, 0));
        // base case:
        // dp[0][j] = costs[0][j], only the house[0] is painted
        for (int j = 0; j < k; ++j) {
            dp[0][j] = costs[0][j];
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                // find min(dp[i-1][k], for all k != j)
                int min = INT_MAX;
                for (int p = 0; p < k; ++p) {
                    if (p == j)
                        continue;

                    min = std::min(min, dp[i - 1][p]);
                }
                dp[i][j] = costs[i][j] + min;
            }
        }
        int result = INT_MAX;
        for (const auto& val : dp[n - 1]) {
            result = std::min(result, val);
        }
        return result;
    }
};