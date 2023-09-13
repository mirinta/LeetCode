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
        static constexpr int kFresh = 1;
        static constexpr int kRotten = 2;
        static const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        const int m = grid.size();
        const int n = grid[0].size();
        int numOfFreshOranges = 0;
        std::vector<std::vector<int>> visited(m, std::vector<int>(n, false));
        std::queue<std::pair<int, int>> queue;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == kRotten) {
                    queue.push({i, j});
                    visited[i][j] = true;
                } else if (grid[i][j] == kFresh) {
                    numOfFreshOranges++;
                }
            }
        }
        if (numOfFreshOranges == 0)
            return 0; // no fresh oranges

        if (queue.empty())
            return -1; // no rotten oranges

        int time = 0;
        while (!queue.empty() && numOfFreshOranges) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto [x, y] = queue.front();
                queue.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    if (!visited[i][j] && grid[i][j] == kFresh) {
                        visited[i][j] = true;
                        queue.push({i, j});
                        numOfFreshOranges--;
                    }
                }
            }
            time++;
        }
        return numOfFreshOranges == 0 ? time : -1;
    }
};