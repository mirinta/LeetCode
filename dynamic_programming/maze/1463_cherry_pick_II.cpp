#include <vector>

/**
 * You are given a rows x cols matrix grid representing a field of cherries where grid[i][j]
 * represents the number of cherries that you can collect from the (i, j) cell.
 *
 * You have two robots that can collect cherries for you:
 *
 * - Robot #1 is located at the top-left corner (0, 0), and
 *
 * - Robot #2 is located at the top-right corner (0, cols - 1).
 *
 * Return the maximum number of cherries collection using both robots by following the rules below:
 *
 * - From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).
 *
 * - When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty
 * cell.
 *
 * - When both robots stay in the same cell, only one takes the cherries.
 *
 * - Both robots cannot move outside of the grid at any moment.
 *
 * - Both robots should reach the bottom row in grid.
 *
 * ! rows == grid.length
 * ! cols == grid[i].length
 * ! 2 <= rows, cols <= 70
 * ! 0 <= grid[i][j] <= 100
 */

class Solution
{
public:
    int cherryPickup(std::vector<std::vector<int>>& grid) { return approach2(grid); }

private:
    // DP with space optimization, TC = O(MN^2), SC = O(N^2)
    int approach2(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, INT_MIN));
        dp[0][n - 1] = grid[0][0] + grid[0][n - 1]; // constraints: cols >= 2
        std::vector<std::vector<int>> prev(n, std::vector<int>(n, INT_MIN));
        int result = INT_MIN;
        for (int i = 1; i < m; ++i) {
            prev.assign(dp.begin(), dp.end());
            for (int j1 = 0; j1 < n; ++j1) {
                for (int j2 = 0; j2 < n; ++j2) {
                    for (int prevJ1 = j1 - 1; prevJ1 <= j1 + 1; ++prevJ1) {
                        for (int prevJ2 = j2 - 1; prevJ2 <= j2 + 1; ++prevJ2) {
                            if (prevJ1 < 0 || prevJ1 >= n || prevJ2 < 0 || prevJ2 >= n)
                                continue;

                            if (j1 != j2) {
                                dp[j1][j2] = std::max(
                                    dp[j1][j2], prev[prevJ1][prevJ2] + grid[i][j1] + grid[i][j2]);
                            } else {
                                dp[j1][j2] =
                                    std::max(dp[j1][j2], prev[prevJ1][prevJ2] + grid[i][j1]);
                            }
                        }
                    }
                    if (i == m - 1) {
                        result = std::max(result, dp[j1][j2]);
                    }
                }
            }
        }
        return result;
    }

    // DP, TC = O(MN^2), SC = O(MN^2)
    int approach1(const std::vector<std::vector<int>>& grid)
    {
        // dp[i][j1][j2] = max num of cherries collection from row 0 to row i
        // while Robot1 is located at grid[i][j1] and Robot2 is located at grid[i][j2]
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<std::vector<int>>> dp(
            m, std::vector<std::vector<int>>(n, std::vector<int>(n, INT_MIN)));
        dp[0][0][n - 1] = grid[0][0] + grid[0][n - 1]; // constraints: cols >= 2
        int result = INT_MIN;
        for (int i = 1; i < m; ++i) {
            for (int j1 = 0; j1 < n; ++j1) {
                for (int j2 = 0; j2 < n; ++j2) {
                    for (int prevJ1 = j1 - 1; prevJ1 <= j1 + 1; ++prevJ1) {
                        for (int prevJ2 = j2 - 1; prevJ2 <= j2 + 1; ++prevJ2) {
                            if (prevJ1 < 0 || prevJ1 >= n || prevJ2 < 0 || prevJ2 >= n)
                                continue;

                            if (j1 != j2) {
                                dp[i][j1][j2] =
                                    std::max(dp[i][j1][j2],
                                             dp[i - 1][prevJ1][prevJ2] + grid[i][j1] + grid[i][j2]);
                            } else {
                                dp[i][j1][j2] = std::max(dp[i][j1][j2],
                                                         dp[i - 1][prevJ1][prevJ2] + grid[i][j1]);
                            }
                        }
                    }
                    if (i == m - 1) {
                        result = std::max(result, dp[i][j1][j2]);
                    }
                }
            }
        }
        return result;
    }
};