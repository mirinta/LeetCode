#include <queue>
#include <vector>

/**
 * Given an n x n binary matrix "grid", return the length of the shortest clear path in the matrix.
 * If there is no clear path, return -1.
 *
 * A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the
 * bottom-right cell (i.e., (n - 1, n - 1)) such that:
 *
 * - All the visited cells of the path are 0.
 *
 * - All the adjacent cells of the path are 8-directionally connected (i.e., they are different and
 * they share an edge or a corner).
 *
 * The length of a clear path is the number of visited cells of this path.
 *
 * ! n == grid.length
 * ! n == grid[i].length
 * ! 1 <= n <= 100
 * ! grid[i][j] is 0 or 1
 */

class Solution
{
public:
    int shortestPathBinaryMatrix(std::vector<std::vector<int>>& grid)
    {
        if (grid.empty() || grid[0].empty())
            return -1;

        const int m = grid.size();
        const int n = grid[0].size();
        if (grid[0][0] != 0 || grid[m - 1][n - 1] != 0)
            return -1;

        static const std::vector<std::pair<int, int>> kDirections{
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        std::queue<std::pair<int, int>> queue;
        queue.push({0, 0});
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        visited[0][0] = true;
        int length = 1;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto [i, j] = queue.front();
                queue.pop();
                if (i == m - 1 && j == n - 1)
                    return length;

                for (const auto& [dx, dy] : kDirections) {
                    const int x = i + dx;
                    const int y = j + dy;
                    if (x < 0 || x >= m || y < 0 || y >= n)
                        continue;

                    if (visited[x][y] || grid[x][y] != 0)
                        continue;

                    visited[x][y] = true;
                    queue.push({x, y});
                }
            }
            length++;
        }
        return -1;
    }
};