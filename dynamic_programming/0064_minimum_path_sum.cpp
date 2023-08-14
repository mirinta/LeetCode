#include <vector>

/**
 * Given a "m x n" "grid" filled with non-negative numbers, find a path from top left to bottom
 * right, which minimizes the sum of all numbers along its path.
 *
 * Note: You can only move either down or right at any point in time.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 200
 * ! 0 <= grid[i][j] <= 200
 */

class Solution
{
public:
    int minPathSum(std::vector<std::vector<int>>& grid) { return approach2(grid); }

private:
    // 1D-DP, time O(MN), space O(N)
    int approach2(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<int> dp(n, 0);
        std::vector<int> iMinus1(n, 0);
        iMinus1[0] = grid[0][0];
        for (int j = 1; j < n; ++j) {
            iMinus1[j] = iMinus1[j - 1] + grid[0][j];
        }
        for (int i = 1; i < m; ++i) {
            dp[0] = iMinus1[0] + grid[i][0];
            for (int j = 1; j < n; ++j) {
                dp[j] = grid[i][j] + std::min(iMinus1[j], dp[j - 1]);
            }
            std::swap(iMinus1, dp);
        }
        return iMinus1[n - 1];
    }

    // 2D-DP, time O(MN), space O(MN)
    int approach1(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        // dp[i][j] = min path sum from (0,0) to (i,j)
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        // base cases:
        // - dp[i][0] = sum(grid[0][0]...grid[i][0])
        // - dp[0][j] = sum[grid[0][0]...grid[0][j])
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; ++i) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = grid[i][j] + std::min(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m - 1][n - 1];
    }
};