#include <vector>

/**
 * Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally
 * connected group of 0s and a closed island is an island totally (all left, top, right, bottom)
 * surrounded by 1s.
 *
 * Return the number of closed islands.
 *
 * ! 1 <= grid.length, grid[0].length <= 100
 * ! 0 <= grid[i][j] <=1
 */

class Solution
{
public:
    int closedIsland(std::vector<std::vector<int>>& grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;

        const int m = grid.size();
        const int n = grid[0].size();
        // flood lands connected with those lands on the boundary
        for (int i = 0; i < m; ++i) {
            dfs(i, 0, grid);
            dfs(i, n - 1, grid);
        }
        for (int j = 0; j < n; ++j) {
            dfs(0, j, grid);
            dfs(m - 1, j, grid);
        }
        int result = 0;
        for (int i = 1; i < m - 1; ++i) {
            for (int j = 1; j < n - 1; ++j) {
                if (grid[i][j] == kLand) {
                    result++;
                    dfs(i, j, grid);
                }
            }
        }
        return result;
    }

private:
    static constexpr int kLand = 0;
    static constexpr int kWater = 1;

    void dfs(int x, int y, std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n)
            return;

        if (grid[x][y] != kLand)
            return;

        grid[x][y] = kWater;
        dfs(x + 1, y, grid);
        dfs(x - 1, y, grid);
        dfs(x, y + 1, grid);
        dfs(x, y - 1, grid);
    }
};