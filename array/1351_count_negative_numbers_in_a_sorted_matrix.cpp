#include <vector>

/**
 * Given a m x n matrix "grid" which is sorted in non-increasing order both row-wise and
 * column-wise, return the number of negative numbers in "grid".
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 100
 * ! -100 <= grid[i][j] <= 100
 */

class Solution
{
public:
    int countNegatives(const std::vector<std::vector<int>>& grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;

        const auto m = grid.size();
        const auto n = grid[0].size();
        // top-left is the global max
        if (grid[0][0] < 0)
            return m * n;

        // bottom-right is the global min
        if (grid[m - 1][n - 1] >= 0)
            return 0;

        // use top-right as pivot
        int row = 0;
        int col = n - 1;
        int result = 0;
        while (row < m && col >= 0) {
            const auto& pivot = grid[row][col];
            if (pivot < 0) {
                result += m - row;
                col--;
            } else {
                row++;
            }
        }
        return result;
    }
};