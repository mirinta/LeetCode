#include <queue>
#include <vector>

/**
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return
 * the number of islands.
 *
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or
 * vertically. You may assume all four edges of the grid are all surrounded by water.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 300
 * ! grid[i][j] is '0' or '1'.
 */

class Solution
{
public:
    int numIslands(std::vector<std::vector<char>>& grid) { return approach1(grid); }

private:
    const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    // BFS, time O(MN), space O(MN)
    int approach2(const std::vector<std::vector<char>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        std::queue<std::pair<int, int>> queue;
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != '1' || visited[i][j])
                    continue;

                visited[i][j] = true;
                queue.push({i, j});
                while (!queue.empty()) {
                    const int size = queue.size();
                    for (int k = 0; k < size; ++k) {
                        const auto [x, y] = queue.front();
                        queue.pop();
                        for (const auto& [dx, dy] : kDirections) {
                            const int p = x + dx;
                            const int q = y + dy;
                            if (p < 0 || p >= m || q < 0 || q >= n)
                                continue;

                            if (grid[p][q] == '1' && !visited[p][q]) {
                                visited[p][q] = true;
                                queue.push({p, q});
                            }
                        }
                    }
                }
                result++;
            }
        }
        return result;
    }

    // DFS, time O(MN), space O(MN)
    int approach1(const std::vector<std::vector<char>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    dfs(visited, i, j, grid);
                    result++;
                }
            }
        }
        return result;
    }

    void dfs(std::vector<std::vector<bool>>& visited, int x, int y,
             const std::vector<std::vector<char>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        visited[x][y] = true;
        for (const auto& [dx, dy] : kDirections) {
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= m || j < 0 || j >= n)
                continue;

            if (!visited[i][j] && grid[i][j] == '1') {
                dfs(visited, i, j, grid);
            }
        }
    }
};
