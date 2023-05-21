#include <vector>

/**
 * Given an "m x n" binary matrix filled with 0's and 1's, find the largest square containing only
 * 1's and return its area.
 *
 * ! matrix[i][j] is '0' or '1'.
 */

class Solution
{
public:
    int maximalSquare(std::vector<std::vector<char>>& matrix)
    {
        if (matrix.empty())
            return 0;

        const auto m = matrix.size();
        const auto n = matrix[0].size();
        // dp[i][j] = length of the largest square whose bottom-right is matrix[i][j]
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        // base cases:
        // - dp[i][0], each point of the first column
        // - dp[0][j], each point of the first row
        for (int i = 0; i < m; ++i) {
            dp[i][0] = matrix[i][0] == '0' ? 0 : 1;
        }
        for (int j = 0; j < n; ++j) {
            dp[0][j] = matrix[0][j] == '0' ? 0 : 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == '1') {
                    dp[i][j] = 1 + std::min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
                } else {
                    dp[i][j] = 0;
                }
            }
        }
        // find the max length
        int length = INT_MIN;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                length = std::max(length, dp[i][j]);
            }
        }
        return length * length;
    }
};