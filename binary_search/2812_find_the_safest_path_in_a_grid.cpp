#include <queue>
#include <vector>

/**
 * You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:
 *
 * - A cell containing a thief if grid[r][c] = 1
 *
 * - An empty cell if grid[r][c] = 0
 *
 * You are initially positioned at cell (0, 0). In one move, you can move to any adjacent cell in
 * the grid, including cells containing thieves.
 *
 * The safeness factor of a path on the grid is defined as the minimum manhattan distance from any
 * cell in the path to any thief in the grid.
 *
 * Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).
 *
 * An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r -
 * 1, c) if it exists.
 *
 * The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|, where
 * |val| denotes the absolute value of val.
 *
 * ! 1 <= grid.length == n <= 400
 * ! grid[i].length == n
 * ! grid[i][j] is either 0 or 1.
 * ! There is at least one thief in the grid.
 */

class Solution
{
public:
    int maximumSafenessFactor(std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        const auto minDist = getMinDistMatrix(grid);
        int lo = 0;
        int hi = 2 * n;
        while (lo < hi) {
            const int mid = hi - (hi - lo) / 2;
            if (isValid(mid, minDist, grid)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return hi;
    }

private:
    const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // check if there exists a path from (0,0) to (n-1,n-1) with safeness >= min
    bool isValid(int min, const std::vector<std::vector<int>>& minDist,
                 const std::vector<std::vector<int>>& grid)
    {
        if (minDist[0][0] < min)
            return false;

        const int n = grid.size();
        std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
        visited[0][0] = true;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(0, 0);
        while (!queue.empty()) {
            const auto [x, y] = queue.front();
            queue.pop();
            if (x == n - 1 && y == n - 1)
                return true;

            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= n || j < 0 || j >= n)
                    continue;

                if (!visited[i][j] && minDist[i][j] >= min) {
                    visited[i][j] = true;
                    queue.emplace(i, j);
                }
            }
        }
        return false;
    }

    // minDist[i][j] = manhattan distance between (i,j) and the nearest thief
    std::vector<std::vector<int>> getMinDistMatrix(const std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        std::vector<std::vector<int>> minDist(n, std::vector<int>(n, -1));
        std::queue<std::pair<int, int>> queue;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    queue.emplace(i, j);
                    minDist[i][j] = 0;
                }
            }
        }
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= n || j < 0 || j >= n)
                        continue;

                    if (minDist[i][j] == -1) {
                        minDist[i][j] = minDist[x][y] + 1;
                        queue.emplace(i, j);
                    }
                }
            }
        }
        return minDist;
    }
};