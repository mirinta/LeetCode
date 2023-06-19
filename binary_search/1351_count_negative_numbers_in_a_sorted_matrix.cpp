#include <algorithm>
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
    int countNegatives(std::vector<std::vector<int>>& grid) { return approach2(grid); }

private:
    // approach2: time O(mlogn), space O(1)
    int approach2(std::vector<std::vector<int>>& grid)
    {
        if (grid.empty())
            return 0;

        const int m = grid.size();
        const int n = grid[0].size();
        if (grid[m - 1][n - 1] >= 0)
            return 0;

        int result = 0;
        for (const auto& row : grid) {
            const int index = std::distance(
                row.begin(), std::upper_bound(row.begin(), row.end(), 0, std::greater<int>{}));
            result += (n - index);
        }
        return result;
    }

    // approach1: time O(m+n), space O(1)
    int approach1(std::vector<std::vector<int>>& grid)
    {
        if (grid.empty())
            return 0;

        //  4  3  2 -1
        //  3  2  1 -1
        //  1  1 -1 -2
        // -1 -1 -2 -3
        const int m = grid.size();
        const int n = grid[0].size();
        // top-left is the largest element
        // bottom-right is the smallest element
        if (grid[m - 1][n - 1] >= 0)
            return 0;

        // always check top-right: grid[x][y]
        // - it is the largest of column y
        // - it is the smallest of row x
        int result = 0;
        int row = 0;
        int col = n - 1;
        while (row < m && col >= 0) {
            if (grid[row][col] < 0) {
                result += m - row;
                col--;
            } else {
                row++;
            }
        }
        return result;
    }
};