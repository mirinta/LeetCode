#include <vector>

/**
 * You are given an m x n integer matrix matrix with the following two properties:
 *
 * Each row is sorted in non-decreasing order.
 * The first integer of each row is greater than the last integer of the previous row.
 * Given an integer target, return true if target is in matrix or false otherwise.
 *
 * You must write a solution in O(log(m * n)) time complexity.
 *
 * ! m == matrix.length
 * ! n == matrix[i].length
 * ! 1 <= m, n <= 100
 * ! -10^4 <= matrix[i][j], target <= 10^4
 */

class Solution
{
public:
    bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target)
    {
        if (matrix.empty() || matrix[0].empty())
            return false;

        const int m = matrix.size();
        const int n = matrix[0].size();
        // flatten the matrix and apply binary search:
        int lo = 0;
        int hi = m * n - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            const int row = mid / n;
            const int col = mid % n;
            if (matrix[row][col] == target)
                return true;

            if (matrix[row][col] > target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return false;
    }
};
