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
    int minFallingPathSum(std::vector<std::vector<int>>& grid) { return approach2(grid); }

private:
    // DP with time optimization, TC = O(N^2), SC = O(N^2)
    int approach2(const std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n));
        for (int j = 0; j < n; ++j) {
            dp[0][j] = grid[0][j];
        }
        for (int i = 1; i < n; ++i) {
            const auto [minIndex, secondMinIndex] = helper(dp[i - 1]);
            for (int j = 0; j < n; ++j) {
                if (j != minIndex) {
                    dp[i][j] = grid[i][j] + dp[i - 1][minIndex];
                } else {
                    dp[i][j] = grid[i][j] + dp[i - 1][secondMinIndex];
                }
            }
        }
        return *std::min_element(dp[n - 1].begin(), dp[n - 1].end());
    }

    std::pair<int, int> helper(const std::vector<int>& nums)
    {
        int minIndex = 0;
        int secondMinIndex = nums.size() - 1;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] < nums[minIndex]) {
                std::swap(minIndex, secondMinIndex);
                minIndex = i;
            } else if (nums[i] < nums[secondMinIndex]) {
                secondMinIndex = i;
            }
        }
        return {minIndex, secondMinIndex};
    }

    // DP, TC = O(N^3), SC = O(N^2)
    int approach1(const std::vector<std::vector<int>>& grid)
    {
        // dp[i][j] = min falling sum from the first row to grid[i][j]
        const int n = grid.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n));
        for (int j = 0; j < n; ++j) {
            dp[0][j] = grid[0][j];
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (k == j)
                        continue;

                    dp[i][j] = std::min(dp[i][j], grid[i][j] + dp[i - 1][k]);
                }
            }
        }
        return *std::min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};