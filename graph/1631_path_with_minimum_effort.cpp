#include <climits>
#include <cmath>
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
    int minimumEffortPath(const std::vector<std::vector<int>>& heights)
    {
        if (heights.empty())
            return -1;

        const auto rows = heights.size();
        const auto cols = heights.front().size();
        std::vector<std::vector<int>> effortTo(rows, std::vector<int>(cols, INT_MAX));
        effortTo[0][0] = 0;
        using Point = std::pair<int, int>; // position x and y
        // directions: go up, go down, go left, go right
        const std::vector<std::pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        std::priority_queue<std::tuple<int, int, int>> minHeap; // <-1 * effort, x, y>
        minHeap.push({0, 0, 0});
        while (!minHeap.empty()) {
            const auto [_, x, y] = minHeap.top();
            minHeap.pop();
            // reach the target position, return
            if (x == rows - 1 && y == cols - 1)
                return effortTo[x][y];

            for (const auto& d : directions) {
                const auto x1 = x + d.first;
                const auto y1 = y + d.second;
                if (x1 < 0 || x1 >= rows || y1 < 0 || y1 >= cols)
                    continue;

                const auto newEffort =
                    std::max(effortTo[x][y], std::abs(heights[x][y] - heights[x1][y1]));
                if (effortTo[x1][y1] > newEffort) {
                    effortTo[x1][y1] = newEffort;
                    minHeap.push({-newEffort, x1, y1});
                }
            }
        }
        return -1;
    }
};
