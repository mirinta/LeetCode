#include <queue>
#include <vector>

/**
 * There is a ball in a maze with empty spaces (represented as 0) and walls (represented as 1). The
 * ball can go through the empty spaces by rolling up, down, left or right, but it won't stop
 * rolling until hitting a wall. When the ball stops, it could choose the next direction.
 *
 * Given the m x n maze, the ball's start position and the destination, where start = [start_row,
 * start_col] and destination = [destination_row, destination_col], return the shortest distance for
 * the ball to stop at the destination. If the ball cannot stop at destination, return -1.
 *
 * The distance is the number of empty spaces traveled by the ball from the start position
 * (excluded) to the destination (included).
 *
 * You may assume that the borders of the maze are all walls (see examples).
 *
 * ! m == maze.length
 * ! n == maze[i].length
 * ! 1 <= m, n <= 100
 * ! maze[i][j] is 0 or 1.
 * ! start.length == 2
 * ! destination.length == 2
 * ! 0 <= start_row, destination_row < m
 * ! 0 <= start_col, destination_col < n
 * ! Both the ball and the destination exist in an empty space, and they will not be in the same
 * ! position initially.
 * ! The maze contains at least 2 empty spaces.
 */

class Solution
{
public:
    // Dijkstra, time O(MNlog(MN)), space O(MN)
    int shortestDistance(std::vector<std::vector<int>>& maze, std::vector<int>& start,
                         std::vector<int>& destination)
    {
        const int m = maze.size();
        const int n = maze[0].size();
        std::vector<std::vector<int>> distTo(m, std::vector<int>(n, INT_MAX));
        distTo[start[0]][start[1]] = 0;
        using Tuple = std::tuple<int, int, int>; // <dist, x, y>
        auto comparator = [](const auto& t1, const auto& t2) {
            return std::get<0>(t1) > std::get<0>(t2);
        };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(comparator)> pq(
            comparator); // min heap
        pq.push({0, start[0], start[1]});
        const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (!pq.empty()) {
            const auto [dist, x, y] = pq.top();
            pq.pop();
            if (x == destination[0] && y == destination[1])
                return dist;

            for (const auto& [dx, dy] : kDirections) {
                int count = 0;
                int i = x + dx;
                int j = y + dy;
                while (i >= 0 && i < m && j >= 0 && j < n && maze[i][j] == 0) {
                    count++;
                    i += dx;
                    j += dy;
                }
                if (count == 0)
                    continue;

                i -= dx;
                j -= dy;
                if (distTo[i][j] > dist + count) {
                    distTo[i][j] = dist + count;
                    pq.push({distTo[i][j], i, j});
                }
            }
        }
        return -1;
    }
};