#include <vector>

/**
 * Given a "m x n" "grid" filled with non-negative numbers, find a path from top left to bottom
 * right, which minimizes the sum of all numbers along its path.
 *
 * ! Note: You can only move either down or right at any point in time.
 *
 * Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
 * Output: 7
 * Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
 */

class Solution
{
public:
    int minPathSum(std::vector<std::vector<int>>& grid)
    {
        if (grid.empty())
            return -1;

        const auto m = grid.size();
        const auto n = grid[0].size();
        // dp[i][j] = min path sum from point(0,0) to point(i,j)
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        // base cases:
        // - dp[0][0] = grid[0][0]
        // - for any i!=0, dp[i][0] = dp[i-1][0] + grid[i][0], prefix sum of the first column
        // - for any j!=0, dp[0][j] = dp[0][j-1] + grid[0][j], prefix sum of the first row
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; ++i) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        // dp[i][0] and dp[0][j] are processed as base cases
        // thus, both i and j start from 1
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                // only two points that can move to point(i, j):
                // - point(i, j-1) and point(i+1, j)
                dp[i][j] = grid[i][j] + std::min(dp[i][j - 1], dp[i - 1][j]);
            }
        }
        return dp[m - 1][n - 1];
    }
};