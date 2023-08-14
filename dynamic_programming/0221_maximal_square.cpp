#include <vector>

/**
 * Given an "m x n" binary matrix filled with 0's and 1's, find the largest square containing only
 * 1's and return its area.
 *
 * ! m == matrix.length
 * ! n == matrix[i].length
 * ! 1 <= m, n <= 300
 * ! matrix[i][j] is '0' or '1'.
 */

class Solution
{
public:
    int maximalSquare(std::vector<std::vector<char>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        // dp[i][j] = length of the largest square whose bottom-right corner is (i,j)
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        // base cases:
        for (int i = 0; i < m; ++i) {
            dp[i][0] = matrix[i][0] == '1' ? 1 : 0;
        }
        for (int j = 0; j < n; ++j) {
            dp[0][j] = matrix[0][j] == '1' ? 1 : 0;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == '0') {
                    dp[i][j] = 0;
                } else {
                    // case1: there's a rectangle of length length_A whose bottom-right corner is A
                    //     |
                    // --- A B
                    //     C X
                    // case2: there's a rectangle of length length_B whose bottom-right corner is B
                    //       |
                    // --- A B
                    //     C X
                    // case3: there's a rectangle of length length_C whose bottom-right corner is B
                    //     |
                    //     A B
                    // --- C X
                    dp[i][j] = 1 + std::min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
                }
            }
        }
        int maxLength = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                maxLength = std::max(maxLength, dp[i][j]);
            }
        }
        return maxLength * maxLength;
    }
};
