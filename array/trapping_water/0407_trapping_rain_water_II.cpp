#include <queue>
#include <vector>

/**
 * Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D
 * elevation map, return the volume of water it can trap after raining.
 *
 * ! m == heightMap.length
 * ! n == heightMap[i].length
 * ! 1 <= m, n <= 200
 * ! 0 <= heightMap[i][j] <= 2 * 10^4
 */

class Solution
{
public:
    int trapRainWater(std::vector<std::vector<int>>& heightMap)
    {
        const int m = heightMap.size();
        const int n = heightMap[0].size();
        std::vector<std::vector<int>> visited(m, std::vector<int>(n, false));
        using Tuple = std::tuple<int, int, int>; // <height, x, y>
        auto comparator = [](const auto& t1, const auto& t2) {
            return std::get<0>(t1) > std::get<0>(t2);
        };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(comparator)> pq(
            comparator); // min heap
        for (int i = 0; i < m; ++i) {
            pq.push({heightMap[i][0], i, 0});
            visited[i][0] = true;
            pq.push({heightMap[i][n - 1], i, n - 1});
            visited[i][n - 1] = true;
        }
        for (int j = 1; j < n - 1; ++j) {
            pq.push({heightMap[0][j], 0, j});
            visited[0][j] = true;
            pq.push({heightMap[m - 1][j], m - 1, j});
            visited[m - 1][j] = true;
        }
        const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int seaLevel = 0;
        int result = 0;
        while (!pq.empty()) {
            const auto [h, x, y] = pq.top();
            pq.pop();
            if (h > seaLevel) {
                seaLevel = h;
            }
            result += seaLevel - h;
            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n)
                    continue;

                if (!visited[i][j]) {
                    visited[i][j] = true;
                    pq.push({heightMap[i][j], i, j});
                }
            }
        }
        return result;
    }
};