#include <vector>

/**
 * You are given an "m x n" integer array "grid". There is a robot initially located at the top-left
 * corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m -
 * 1][n - 1]). The robot can only move either down or right at any point in time.
 *
 * An obstacle and space are marked as 1 or 0 respectively in grid. A path that the robot takes
 * cannot include any square that is an obstacle.
 *
 * Return the number of possible unique paths that the robot can take to reach the bottom-right
 * corner.
 *
 * The text cases are generated so that the answer will be less than or equal to 2 * 10^9.
 */

class Solution
{
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid)
    {
        if (obstacleGrid.empty())
            return 0;

        const auto m = obstacleGrid.size();
        const auto n = obstacleGrid[0].size();
        if (obstacleGrid[0][0] || obstacleGrid[m - 1][n - 1])
            return 0;

        // approach 1:
        // dp[i][j] = number of paths from pos(0,0) to pos(i,j)
        // base cases:
        // - dp[0][0], dp[i][0], dp[0][j]
        std::vector<std::vector<long long>> dp(m, std::vector<long long>(n, 0));
        dp[0][0] = 1;
        for (int i = 1; i < m; ++i) {
            dp[i][0] = !obstacleGrid[i][0] && dp[i - 1][0] ? 1 : 0;
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = !obstacleGrid[0][j] && dp[0][j - 1] ? 1 : 0;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (obstacleGrid[i][j]) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
                }
            }
        }
        return dp[m - 1][n - 1];

        // approach 2:
        // dp[i][j] = number of paths from pos(i,j) to bottom-right
        // base cases:
        // - dp[m - 1][n - 1] = 1, already at the destination
        // - dp[m - 1][j], start from any pos in the last row
        // - dp[i][n - 1], start from any pos in the last column
        // std::vector<std::vector<long long>> dp(m, std::vector<long long>(n, 0));
        // dp[m - 1][n - 1] = 1;
        // for (int i = m - 2; i >= 0; --i) {
        //     dp[i][n - 1] = !obstacleGrid[i][n - 1] && dp[i + 1][n - 1] ? 1 : 0;
        // }
        // for (int j = n - 2; j >= 0; --j) {
        //     dp[m - 1][j] = !obstacleGrid[m - 1][j] && dp[m - 1][j + 1] ? 1 : 0;
        // }
        // for (int i = m - 2; i >= 0; --i) {
        //     for (int j = n - 2; j >= 0; --j) {
        //         if (obstacleGrid[i][j]) {
        //             dp[i][j] = 0;
        //         } else {
        //             dp[i][j] = (dp[i][j + 1] + dp[i + 1][j]);
        //         }
        //     }
        // }
        // return dp[0][0];
    }
};