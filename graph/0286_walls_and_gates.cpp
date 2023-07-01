#include <queue>
#include <vector>

/**
 * You are given an m x n grid rooms initialized with these three possible values.
 *
 * - -1 A wall or an obstacle.
 * - 0 A gate.
 * - INF Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you
 * may assume that the distance to a gate is less than 2147483647.
 *
 * Fill each empty room with the
 * distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.
 *
 * ! m == rooms.length
 * ! n == rooms[i].length
 * ! 1 <= m, n <= 250
 * ! rooms[i][j] is -1, 0, or 2^31 - 1.
 */

class Solution
{
public:
    void wallsAndGates(std::vector<std::vector<int>>& rooms)
    {
        constexpr int kGate = 0;
        constexpr int kInitRoom = INT_MAX;
        if (rooms.empty() || rooms[0].empty())
            return;

        const int m = rooms.size();
        const int n = rooms[0].size();
        std::queue<std::pair<int, int>> queue;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rooms[i][j] == kGate) {
                    queue.push({i, j});
                }
            }
        }
        const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (!queue.empty()) {
            const auto [x, y] = queue.front();
            queue.pop();
            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n)
                    continue;

                if (rooms[i][j] != kInitRoom)
                    continue;

                rooms[i][j] = rooms[x][y] + 1;
                queue.push({i, j});
            }
        }
    }
};