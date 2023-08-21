#include <vector>

/**
 * Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 1 <= m, n <= 10^4
 * ! 1 <= m * n <= 10^4
 * ! -10^5 <= mat[i][j] <= 10^5
 */

class Solution
{
public:
    // simulation, time O(MN), space O(1)
    std::vector<int> findDiagonalOrder(std::vector<std::vector<int>>& mat)
    {
        // start from (i,j)
        // - go upper right: (i-1,j+1),(i-2,j+2),...
        // - go bottom left: (i+1,j-1),(i+2,j-2),...
        const int m = mat.size();
        const int n = mat[0].size();
        int direction = 1; // 1 for upper right, -1 for bottom left
        int count = m * n;
        int x = 0;
        int y = 0;
        std::vector<int> result;
        while (count) {
            while (x >= 0 && x < m && y >= 0 && y < n) {
                result.push_back(mat[x][y]);
                x -= direction;
                y += direction;
                count--;
            }
            if (direction > 0) {
                x = y >= n ? x + 2 : 0;
                y = y >= n ? n - 1 : y;
            } else {
                y = x >= m ? y + 2 : 0;
                x = x >= m ? m - 1 : x;
            }
            direction *= -1;
        }
        return result;
    }
};