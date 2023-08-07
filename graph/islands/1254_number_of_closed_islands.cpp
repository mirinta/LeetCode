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
    // DFS, time O(MN), space O(MN)
    int closedIsland(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            if (grid[i][0] == kLand && !visited[i][0]) {
                dfs(visited, i, 0, grid);
            }
            if (grid[i][n - 1] == kLand && !visited[i][n - 1]) {
                dfs(visited, i, n - 1, grid);
            }
        }
        for (int j = 0; j < n; ++j) {
            if (grid[0][j] == kLand && !visited[0][j]) {
                dfs(visited, 0, j, grid);
            }
            if (grid[m - 1][j] == kLand && !visited[m - 1][j]) {
                dfs(visited, m - 1, j, grid);
            }
        }
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == kLand && !visited[i][j]) {
                    dfs(visited, i, j, grid);
                    result++;
                }
            }
        }
        return result;
    }

private:
    static constexpr int kLand = 0;

    void dfs(std::vector<std::vector<bool>>& visited, int x, int y,
             const std::vector<std::vector<int>>& grid)
    {
        static const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
        const int m = grid.size();
        const int n = grid[0].size();
        visited[x][y] = true;
        for (const auto& [dx, dy] : kDirections) {
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= m || j < 0 || j >= n)
                continue;

            if (!visited[i][j] && grid[i][j] == kLand) {
                dfs(visited, i, j, grid);
            }
        }
    }
};
