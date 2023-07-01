#include <vector>

/**
 * You are given an m x n binary matrix grid. An island is a group of 1's (representing land)
 * connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are
 * surrounded by water.
 *
 * The area of an island is the number of cells with a value 1 in the island.
 *
 * Return the maximum area of an island in grid. If there is no island, return 0.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 50
 * ! grid[i][j] is either 0 or 1.
 */

class Solution
{
public:
    int maxAreaOfIsland(std::vector<std::vector<int>>& grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;

        const int m = grid.size();
        const int n = grid[0].size();
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result = std::max(result, dfs(i, j, grid));
            }
        }
        return result;
    }

private:
    static constexpr int kLand = 1;
    static constexpr int kWater = 0;
    const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int dfs(int x, int y, std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != kLand)
            return 0;

        grid[x][y] = kWater;
        int area = 1;
        for (const auto& [dx, dy] : kDirections) {
            area += dfs(x + dx, y + dy, grid);
        }
        return area;
    }
};