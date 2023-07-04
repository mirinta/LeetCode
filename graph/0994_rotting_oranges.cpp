#include <queue>
#include <vector>

/**
 * You are given an m x n grid where each cell can have one of three values:
 *
 * - 0 representing an empty cell,
 *
 * - 1 representing a fresh orange, or
 *
 * - 2 representing a rotten orange.
 * Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes
 * rotten.
 *
 * Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this
 * is impossible, return -1.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 10
 * ! grid[i][j] is 0, 1, or 2.
 */

class Solution
{
public:
    int orangesRotting(std::vector<std::vector<int>>& grid)
    {
        if (grid.empty() || grid[0].empty())
            return -1;

        const int m = grid.size();
        const int n = grid[0].size();
        const int kRot = 2;
        const int kFresh = 1;
        std::queue<std::pair<int, int>> queue;
        int numOfFreshOranges = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == kRot) {
                    queue.push({i, j});
                } else if (grid[i][j] == kFresh) {
                    numOfFreshOranges++;
                }
            }
        }
        if (numOfFreshOranges == 0)
            return 0;

        const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int time = -1;
        while (!queue.empty()) {
            time++;
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto [x, y] = queue.front();
                queue.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    if (grid[i][j] == kFresh) {
                        grid[i][j] = kRot;
                        numOfFreshOranges--;
                        queue.push({i, j});
                    }
                }
            }
        }
        return numOfFreshOranges == 0 ? time : -1;
    }
};