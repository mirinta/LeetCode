#include <cstddef>
#include <queue>
#include <vector>

/**
 * You are given an "n x n" binary matrix "grid" where 1 represents land and 0 represents water.
 *
 * An island is a 4-directionally connected group of 1's not connected to any other 1's. There are
 * exactly two islands in grid.
 *
 * You may change 0's to 1's to connect the two islands to form on island.
 *
 * Return the smallest number of 0's you must flip to connect the two islands.
 */

class Solution
{
public:
    int shortestBridge(std::vector<std::vector<int>>& grid)
    {
        if (grid.size() < 2)
            return 0;

        // find any land position, say (x,y)
        // DFS: find and store all land positions of the island that contains (x,y),
        // and mark this island as island2 (land value = 2)
        std::queue<std::pair<int, int>> island;
        bool found = false;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == 1) {
                    dfs(i, j, grid, island);
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }
        // BFS: expand island2 until it reaches island1,
        // all points of island2 should move simultaneously
        int dist = 0;
        while (!island.empty()) {
            const auto size = island.size();
            for (size_t i = 0; i < size; ++i) {
                const auto [x, y] = island.front();
                island.pop();
                for (const auto& [x1, y1] : adjacentPoints(x, y, grid.size())) {
                    if (grid[x1][y1] == 1)
                        return dist;

                    if (grid[x1][y1] == 0) {
                        grid[x1][y1] = 3; // mark 3 to represent visited "water"
                        island.push({x1, y1});
                    }
                }
            }
            dist++;
        }
        return dist;
    }

private:
    std::vector<std::pair<int, int>> adjacentPoints(int x, int y, int n)
    {
        if (x < 0 || x >= n || y < 0 || y >= n)
            return {};

        std::vector<std::pair<int, int>> result;
        if (x - 1 >= 0) {
            result.push_back({x - 1, y});
        }
        if (x + 1 < n) {
            result.push_back({x + 1, y});
        }
        if (y - 1 >= 0) {
            result.push_back({x, y - 1});
        }
        if (y + 1 < n) {
            result.push_back({x, y + 1});
        }
        return result;
    }

    void dfs(int startX, int startY, std::vector<std::vector<int>>& grid,
             std::queue<std::pair<int, int>>& island)
    {
        if (grid[startX][startY] == 0 || grid[startX][startY] == 2)
            return;

        grid[startX][startY] = 2;
        island.push({startX, startY});
        for (const auto& [x, y] : adjacentPoints(startX, startY, grid.size())) {
            dfs(x, y, grid, island);
        }
    }
};