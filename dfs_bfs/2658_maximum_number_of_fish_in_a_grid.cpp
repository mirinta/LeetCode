#include <vector>

/**
 * You are given a 0-indexed 2D matrix grid of size m x n, where (r, c) represents:
 *
 * - A land cell if grid[r][c] = 0, or
 *
 * - A water cell containing grid[r][c] fish, if grid[r][c] > 0.
 *
 * A fisher can start at any water cell (r, c) and can do the following operations any number of
 * times:
 *
 * - Catch all the fish at cell (r, c), or
 *
 * - Move to any adjacent water cell.
 *
 * Return the maximum number of fish the fisher can catch if he chooses his starting cell optimally,
 * or 0 if no water cell exists.
 *
 * An adjacent cell of the cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) or (r
 * - 1, c) if it exists.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 10
 * ! 0 <= grid[i][j] <= 10
 */

class Solution
{
public:
    int findMaxFish(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result = std::max(result, dfs(grid, i, j, m, n));
            }
        }
        return result;
    }

private:
    int dfs(std::vector<std::vector<int>>& grid, int i, int j, int m, int n)
    {
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0)
            return 0;

        int result = grid[i][j];
        grid[i][j] = 0;
        result += dfs(grid, i + 1, j, m, n);
        result += dfs(grid, i - 1, j, m, n);
        result += dfs(grid, i, j + 1, m, n);
        result += dfs(grid, i, j - 1, m, n);
        return result;
    }
};