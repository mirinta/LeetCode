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
    int longestIncreasingPath(const std::vector<std::vector<int>>& matrix)
    {
        if (matrix.empty())
            return 0;

        const auto m = matrix.size();
        const auto n = matrix[0].size();
        std::vector<std::vector<int>> memo(m, std::vector<int>(n, 0));
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result = std::max(result, dfs(i, j, memo, matrix));
            }
        }
        return result;
    }

private:
    const std::vector<std::pair<int, int>> kOffsets{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // length of longest increasing path starts from (x,y)
    // - length = num of elements along the path
    int dfs(int x, int y, std::vector<std::vector<int>>& memo,
            const std::vector<std::vector<int>>& matrix)
    {
        const auto m = matrix.size();
        const auto n = matrix[0].size();
        if (memo[x][y] != 0)
            return memo[x][y];

        for (const auto& [dx, dy] : kOffsets) {
            const int newX = x + dx;
            const int newY = y + dy;
            if (newX >= 0 && newX < m && newY >= 0 && newY < n &&
                matrix[newX][newY] > matrix[x][y]) {
                memo[x][y] = std::max(memo[x][y], dfs(newX, newY, memo, matrix));
            }
        }
        memo[x][y] += 1; // the current element
        return memo[x][y];
    }
};