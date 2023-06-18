#include <vector>

/**
 * You are given an m x n integer matrix grid, where you can move from a cell to any adjacent cell
 * in all 4 directions.
 *
 * Return the number of strictly increasing paths in the grid such that you can start from any cell
 * and end at any cell. Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * Two paths are considered different if they do not have exactly the same sequence of visited
 * cells.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 1000
 * ! 1 <= m * n <= 10^5
 * ! 1 <= grid[i][j] <= 10^5
 */

class Solution
{
public:
    int countPaths(const std::vector<std::vector<int>>& grid)
    {
        const auto m = grid.size();
        const auto n = grid[0].size();
        std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result = (result + dfs(i, j, memo, grid)) % kMod;
            }
        }
        return result;
    }

private:
    static constexpr int kMod = 1e9 + 7;
    const std::vector<std::pair<int, int>> kOffsets{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    // num of strictly increasing paths with (x,y) as start point
    int dfs(int x, int y, std::vector<std::vector<int>>& memo,
            const std::vector<std::vector<int>>& grid)
    {
        const auto m = grid.size();
        const auto n = grid[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n)
            return 0;

        if (memo[x][y] != -1)
            return memo[x][y];

        memo[x][y] = 1;
        for (const auto& [dx, dy] : kOffsets) {
            int newX = x + dx;
            int newY = y + dy;
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && grid[newX][newY] > grid[x][y]) {
                memo[x][y] = (memo[x][y] + dfs(newX, newY, memo, grid)) % kMod;
            }
        }
        return memo[x][y];
    }
};