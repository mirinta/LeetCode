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
    // DFS, time O(MN), space O(MN)
    int maxAreaOfIsland(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    result = std::max(result, dfs(visited, i, j, grid));
                }
            }
        }
        return result;
    }

private:
    static constexpr int kLand = 1;
    const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    int dfs(std::vector<std::vector<bool>>& visited, int x, int y,
            const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        visited[x][y] = true;
        int area = 1;
        for (const auto& [dx, dy] : kDirections) {
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= m || j < 0 || j >= n)
                continue;

            if (!visited[i][j] && grid[i][j] == kLand) {
                area += dfs(visited, i, j, grid);
            }
        }
        return area;
    }
};
