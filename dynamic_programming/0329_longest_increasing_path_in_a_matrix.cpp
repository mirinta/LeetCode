#include <vector>

/**
 * Given an m x n integers matrix, return the length of the longest increasing path in matrix.
 *
 * From each cell, you can either move in four directions: left, right, up, or down. You may not
 * move diagonally or move outside the boundary (i.e., wrap-around is not allowed).
 *
 * ! m == matrix.length
 * ! n == matrix[i].length
 * ! 1 <= m, n <= 200
 * ! 0 <= matrix[i][j] <= 2^31 - 1
 */

class Solution
{
public:
    int longestIncreasingPath(std::vector<std::vector<int>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result = std::max(result, dp(memo, i, j, matrix));
            }
        }
        return result;
    }

private:
    static const std::vector<std::pair<int, int>> kDirections;

    // length of the longest increasing path starting from matrix[i][j]
    int dp(std::vector<std::vector<int>>& memo, int x, int y,
           const std::vector<std::vector<int>>& matrix)
    {
        if (memo[x][y] != -1)
            return memo[x][y];

        int result = 1;
        for (const auto& [dx, dy] : kDirections) {
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size())
                continue;

            if (matrix[i][j] > matrix[x][y]) {
                result = std::max(result, 1 + dp(memo, i, j, matrix));
            }
        }
        return memo[x][y] = result;
    }
};

const std::vector<std::pair<int, int>> Solution::kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};