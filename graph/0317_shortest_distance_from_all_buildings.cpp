#include <queue>
#include <vector>

/**
 * You are given an m x n grid grid of values 0, 1, or 2, where:
 *
 * - each 0 marks an empty land that you can pass by freely,
 *
 * - each 1 marks a building that you cannot pass through, and
 *
 * - each 2 marks an obstacle that you cannot pass through.
 *
 * You want to build a house on an empty land that reaches all buildings in the shortest total
 * travel distance. You can only move up, down, left, and right.
 *
 * Return the shortest travel distance for such a house. If it is not possible to build such a house
 * according to the above rules, return -1.
 *
 * The total travel distance is the sum of the distances between the houses of the friends and the
 * meeting point.
 *
 * The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| +
 * |p2.y - p1.y|.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 50
 * ! grid[i][j] is either 0, 1, or 2.
 * ! There will be at least one building in the grid.
 */

class Solution
{
public:
    int shortestDistance(std::vector<std::vector<int>>& grid) { return approach2(grid); }

private:
    const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    // from houses to empty lands, time O((MN)^2), space O(MN)
    int approach2(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        // if grid[i][j] is an empty land,
        // then data[i][j] = <accumulated dist, num of houses can reach this empty land>
        std::vector<std::vector<std::pair<int, int>>> data(
            m, std::vector<std::pair<int, int>>(n, {0, 0}));
        int totalHouses = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    totalHouses++;
                    bfs2(data, i, j, grid);
                }
            }
        }
        int result = INT_MAX;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0 && data[i][j].second == totalHouses) {
                    result = std::min(result, data[i][j].first);
                }
            }
        }
        return result == INT_MAX ? -1 : result;
    }

    void bfs2(std::vector<std::vector<std::pair<int, int>>>& data, int x0, int y0,
              const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        visited[x0][y0] = true;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(x0, y0);
        int steps = 0;
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                if (grid[x][y] == 0) {
                    data[x][y].first += steps;
                    data[x][y].second++;
                }
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    if (visited[i][j] || grid[i][j] != 0)
                        continue;

                    visited[i][j] = true;
                    queue.emplace(i, j);
                }
            }
            steps++;
        }
    }

    // from empty lands to houses, time O((MN)^2), space O(MN)
    int approach1(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        int totalHouses = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    totalHouses++;
                }
            }
        }
        int result = INT_MAX;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    result = std::min(result, bfs1(grid, i, j, totalHouses));
                }
            }
        }
        return result == INT_MAX ? -1 : result;
    }

    int bfs1(std::vector<std::vector<int>>& grid, int x0, int y0, int totalHouses)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        visited[x0][y0] = true;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(x0, y0);
        int total = 0;
        int steps = 0;
        int count = 0;
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                if (grid[x][y] == 1) {
                    total += steps;
                    count++;
                    continue;
                }
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    if (visited[i][j] || grid[i][j] == 2)
                        continue;

                    visited[i][j] = true;
                    queue.emplace(i, j);
                }
            }
            steps++;
        }
        if (count == totalHouses)
            return total;

        // start from (x0,y0), there's at least one house that we can't reach
        // thus, all visited vertices can be marked as obstacles
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0 && visited[i][j]) {
                    grid[i][j] = 2;
                }
            }
        }
        return INT_MAX;
    }
};
