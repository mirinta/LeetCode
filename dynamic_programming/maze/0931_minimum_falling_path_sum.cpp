#include <algorithm>
#include <vector>

/**
 * Given an n x n array of integers matrix, return the minimum sum of any falling path through
 * matrix.
 *
 * A falling path starts at any element in the first row and chooses the element in the next row
 * that is either directly below or diagonally left/right. Specifically, the next element from
 * position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).
 *
 * ! n == matrix.length == matrix[i].length
 * ! 1 <= n <= 100
 * ! -100 <= matrix[i][j] <= 100
 */

class Solution
{
public:
    int minFallingPathSum(std::vector<std::vector<int>>& matrix) { return approach2(matrix); }

private:
    // DP with space optimization, TC = O(N^2), SC = O(N)
    int approach2(const std::vector<std::vector<int>>& matrix)
    {
        const int n = matrix.size();
        auto dp = matrix[0];
        for (int i = 1; i < n; ++i) {
            auto prev = dp;
            std::fill(dp.begin(), dp.end(), INT_MAX);
            for (int j = 0; j < n; ++j) {
                dp[j] = std::min(dp[j], matrix[i][j] + prev[j]);
                if (j - 1 >= 0) {
                    dp[j] = std::min(dp[j], matrix[i][j] + prev[j - 1]);
                }
                if (j + 1 < n) {
                    dp[j] = std::min(dp[j], matrix[i][j] + prev[j + 1]);
                }
            }
        }
        return *std::min_element(dp.begin(), dp.end());
    }

    // DP, TC = O(N^2), SC = O(N^2)
    int approach1(const std::vector<std::vector<int>>& matrix)
    {
        // dp[i][j] = min sum of falling path from first row to cell(i,j)
        const int n = matrix.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, INT_MAX));
        dp[0] = matrix[0];
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[i][j] = std::min(dp[i][j], matrix[i][j] + dp[i - 1][j]);
                if (j - 1 >= 0) {
                    dp[i][j] = std::min(dp[i][j], matrix[i][j] + dp[i - 1][j - 1]);
                }
                if (j + 1 < n) {
                    dp[i][j] = std::min(dp[i][j], matrix[i][j] + dp[i - 1][j + 1]);
                }
            }
        }
        return *std::min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};