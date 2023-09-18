#include <queue>
#include <vector>

/**
 * You are given an m x n matrix maze (0-indexed) with empty cells (represented as '.') and walls
 * (represented as '+'). You are also given the entrance of the maze, where entrance =
 * [entrance_row, entrance_col] denotes the row and column of the cell you are initially standing
 * at.
 *
 * In one step, you can move one cell up, down, left, or right. You cannot step into a cell with a
 * wall, and you cannot step outside the maze. Your goal is to find the nearest exit from the
 * entrance. An exit is defined as an empty cell that is at the border of the maze. The entrance
 * does not count as an exit.
 *
 * Return the number of steps in the shortest path from the entrance to the nearest exit, or -1 if
 * no such path exists.
 *
 * ! maze.length == m
 * ! maze[i].length == n
 * ! 1 <= m, n <= 100
 * ! maze[i][j] is either '.' or '+'.
 * ! entrance.length == 2
 * ! 0 <= entrance_row < m
 * ! 0 <= entrance_col < n
 * ! entrance will always be an empty cell.
 */

class Solution
{
public:
    int nearestExit(std::vector<std::vector<char>>& maze, std::vector<int>& entrance)
    {
        static constexpr char kEmpty = '.';
        static constexpr char kWall = '+';
        const int m = maze.size();
        const int n = maze[0].size();
        const int x0 = entrance[0];
        const int y0 = entrance[1];
        std::queue<std::pair<int, int>> queue;
        for (int i = 0; i < m; ++i) {
            if (maze[i][0] == kEmpty && !isSameLocation(i, 0, x0, y0)) {
                queue.emplace(i, 0);
            }
            if (maze[i][n - 1] == kEmpty && !isSameLocation(i, n - 1, x0, y0)) {
                queue.emplace(i, n - 1);
            }
        }
        for (int j = 1; j < n - 1; ++j) {
            if (maze[0][j] == kEmpty && !isSameLocation(0, j, x0, y0)) {
                queue.emplace(0, j);
            }
            if (maze[m - 1][j] == kEmpty && !isSameLocation(m - 1, j, x0, y0)) {
                queue.emplace(m - 1, j);
            }
        }
        static const std::vector<std::pair<int, int>> kDirections{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int steps = 0;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto [x, y] = queue.front();
                queue.pop();
                if (x == x0 && y == y0)
                    return steps;

                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n || maze[i][j] != kEmpty)
                        continue;

                    maze[i][j] = kWall;
                    queue.emplace(i, j);
                }
            }
            steps++;
        }
        return -1;
    }

private:
    bool isSameLocation(int x1, int y1, int x2, int y2) { return (x1 == x2) && (y1 == y2); }
};
