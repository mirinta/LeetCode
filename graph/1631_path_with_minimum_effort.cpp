#include <array>
#include <climits>
#include <cmath>
#include <tuple>
#include <queue>
#include <vector>

/**
 * Your are a hiker preparing for an upcoming hike. You are given "heights", a 2D array of size row
 * x columns, where hights[row][col] represents the height of cell (row, col). You are situated in
 * the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows - 1, columns -
 * 1). You can move up, down, left, or right, and you wish to find a route that requires the minimum
 * effort.
 *
 * A route's effort is the maximum absolute difference in heights between two consecutive cells of
 * the route.
 *
 * Return the minimum effort required to travel from the top-left cell to the bottom-right cell.
 *
 * ! rows == heights.length
 * ! columns == heights[i].length
 *
 * Example:
 * Input:
 * [1   2   2]
 * [3   8   2]
 * [5   3   5]
 * Output: 2
 * Explanation: The route of [1, 3, 5, 3, 5] has a maximum absolute difference of 2 in consecutive
 * cells. This is better than the route of [1, 2, 2, 2, 5], where the maximum absolute difference
 * is 3.
 */

class Solution
{
public:
    int minimumEffortPath(std::vector<std::vector<int>>& heights) { return approach1(heights); }

private:
    int approach1(std::vector<std::vector<int>>& heights)
    {
        // Dijkstra's algorithm
        if (heights.empty() || heights[0].empty())
            return -1;

        const int m = heights.size();
        const int n = heights[0].size();
        using Triple = std::array<int, 3>; // [effort to this point, x, y]
        auto comp = [](const auto& t1, const auto& t2) -> bool { return t1[0] > t2[0]; };
        std::priority_queue<Triple, std::vector<Triple>, decltype(comp)> pq(comp);
        pq.push({0, 0, 0});
        std::vector<std::vector<int>> effortTo(m, std::vector<int>(n, INT_MAX));
        effortTo[0][0] = 0;
        const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (!pq.empty()) {
            const auto [_, x, y] = pq.top();
            pq.pop();
            if (x == m - 1 && y == n - 1)
                return effortTo[x][y];

            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n)
                    continue;

                const int effort =
                    std::max(effortTo[x][y], std::abs(heights[x][y] - heights[i][j]));
                if (effortTo[i][j] > effort) {
                    effortTo[i][j] = effort;
                    pq.push({effort, i, j});
                }
            }
        }
        return -1;
    }

    int approach2(std::vector<std::vector<int>>& heights)
    {
        // DP with space optimization and early return
        if (heights.empty() || heights[0].empty())
            return -1;

        const int m = heights.size();
        const int n = heights[0].size();
        const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        std::vector<int> dp(m * n, INT_MAX);
        dp[0] = 0;
        bool relaxed = true;
        for (int k = 1; relaxed && k < m * n; ++k) {
            relaxed = false;
            for (int x = 0; x < m; ++x) {
                for (int y = 0; y < n; ++y) {
                    for (const auto& [dx, dy] : kDirections) {
                        const int i = x + dx;
                        const int j = y + dy;
                        if (i < 0 || i >= m || j < 0 || j >= n)
                            continue;

                        if (dp[x * n + y] == INT_MAX)
                            continue;

                        const int diff = std::abs(heights[x][y] - heights[i][j]);
                        const int effort = std::max(dp[x * n + y], diff);
                        if (dp[i * n + j] > effort) {
                            relaxed = true;
                            dp[i * n + j] = effort;
                        }
                    }
                }
            }
        }
        return dp.back();
    }
};
