#include <vector>

/**
 * There is a robot on an "m x n" grid. The robot is initially located at the top-left corner (i.e.,
 * grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The
 * robot can only move either down or right at any point in time.
 *
 * Given the two integers m and n, return the number of possible unique paths that the robot can
 * take to reach the bottom-right corner.
 *
 * The test cases are generated so that the answer will be less than or equal to 2 * 10^9.
 */

class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        if (m < 1 || n < 1)
            return 0;

        // dp[i][j] = number of unique paths from pos(i,j) to pos(m-1,n-1)
        // base cases:
        // - dp[m-1][j] = dp[i][n-1] = 1, last row or last column
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 1));
        for (int i = m - 2; i >= 0; --i) {
            for (int j = n - 2; j >= 0; --j) {
                dp[i][j] = dp[i + 1][j] + dp[i][j + 1];
            }
        }
        return dp[0][0];
    }
};