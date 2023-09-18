#include <algorithm>
#include <vector>

/**
 * Given an n x n integer matrix "grid", return the minimum sum of falling path with non-zero
 * shifts.
 *
 * A falling path with non-zero shifts is a choice of exactly one element from each row of "grid"
 * such that no two elements chosen in adjacent rows are in the same column.
 *
 * ! n == grid.length == grid[i].length
 * ! 1 <= n <= 200
 * ! -99 <= grid[i][j] <= 99
 */

class Solution
{
public:
    int minFallingPathSum(const std::vector<std::vector<int>>& grid)
    {
        if (grid.empty())
            return INT_MAX;

        const auto n = grid.size();
        if (grid[0].size() != n)
            return INT_MAX;

        if (n == 1)
            return grid[0][0];

        // dp[i][j] = min falling sum from first row to grid[i][j]
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        // base case:
        // - dp[0][...] = grid[0][...], falling from first row to first row
        for (int j = 0; j < n; ++j) {
            dp[0][j] = grid[0][j];
        }
        for (int i = 1; i < n; ++i) {
            std::vector<std::pair<int, int>> lastRow;
            lastRow.reserve(n);
            for (int k = 0; k < n; ++k) {
                lastRow.emplace_back(dp[i - 1][k], k);
            }
            std::sort(lastRow.begin(), lastRow.end());
            for (int j = 0; j < n; ++j) {
                // find min value of the last row:
                // int min = INT_MAX;
                // for (int k = 0; k < n; ++k) {
                //     if (j == k)
                //         continue;

                //     min = std::min(min, dp[i - 1][k]);
                // }
                // dp[i][j] = grid[i][j] + min
                if (lastRow[0].second != j) {
                    dp[i][j] = grid[i][j] + lastRow[0].first;
                } else {
                    dp[i][j] = grid[i][j] + lastRow[1].first;
                }
            }
        }
        int result = INT_MAX;
        for (const auto& val : dp[n - 1]) {
            result = std::min(result, val);
        }
        return result;
    }
};
