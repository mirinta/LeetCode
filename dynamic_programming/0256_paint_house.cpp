#include <climits>
#include <vector>

/**
 * There is a row of "n" houses, where each house can be painted one of three colors: red, blue, or
 * green. The cost of painting each house with a certain color is different. You have to paint all
 * the houses such that no two adjacent houses have the same color.
 *
 * The cost of painting each house with a certain color is represented by an n x 3 cost matrix
 * costs.
 *
 * - for example, cost[0][0] is the cost of painting house[0] with the color red; cost[1][2] is the
 * cost of painting house 1 with color green, and so on...
 *
 * Return the minimum cost to paint all houses.
 *
 * ! costs[i].length == 3
 * ! 1 <= costs[i][j]
 */

class Solution
{
public:
    int minCost(std::vector<std::vector<int>>& costs)
    {
        // similar to LC 265 (paint house with k colors)
        if (costs.empty())
            return 0;

        const auto m = costs.size();
        const auto n = costs[0].size();
        // dp[i][j] = min cost of painting house[0:i] while house[i] is painted with color[j]
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        // base case:
        // dp[0][j], min cost of painting house[0] with color[j]
        for (int j = 0; j < n; ++j) {
            dp[0][j] = costs[0][j];
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int min = INT_MAX;
                for (int k = 0; k < n; ++k) {
                    if (k == j)
                        continue;

                    min = std::min(min, dp[i - 1][k]);
                }
                dp[i][j] = min + costs[i][j];
            }
        }
        int result = INT_MAX;
        for (const auto& val : dp[m - 1]) {
            result = std::min(result, val);
        }
        return result;
    }
};