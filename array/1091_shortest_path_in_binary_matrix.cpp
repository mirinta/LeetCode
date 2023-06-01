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
    int shortestPathBinaryMatrix(const std::vector<std::vector<int>>& grid)
    {
        const auto n = grid.size();
        if (n < 1 || grid[0].size() != n)
            return -1;

        if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0)
            return -1;

        std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
        visited[0][0] = true;
        std::queue<std::tuple<int, int, int>> queue; // <x, y, dist>
        queue.emplace(0, 0, 1);                      // goal = num of cells in the shortest path
        while (!queue.empty()) {
            const auto [x, y, dist] = queue.front();
            queue.pop();
            if (x == n - 1 && y == n - 1)
                return dist;

            for (const auto& [i, j] : adjacentCells(x, y, grid)) {
                if (visited[i][j])
                    continue;

                visited[i][j] = true;
                queue.emplace(i, j, dist + 1);
            }
        }
        return -1;
    }

private:
    const std::vector<std::pair<int, int>> offsets{{-1, 0},  {1, 0},  {0, -1}, {0, 1},
                                                   {-1, -1}, {1, -1}, {1, 1},  {-1, 1}};

    std::vector<std::pair<int, int>> adjacentCells(int x, int y,
                                                   const std::vector<std::vector<int>>& grid)
    {
        const auto n = grid.size();
        std::vector<std::pair<int, int>> result;
        for (const auto& [dx, dy] : offsets) {
            const auto i = x + dx;
            const auto j = y + dy;
            if (i >= 0 && i < n && j >= 0 && j < n && grid[i][j] == 0) {
                result.emplace_back(i, j);
            }
        }
        return result;
    }
};