#include <vector>

/**
 * Given an m x n integer matrix, if an element is 0, ste its entire row and column to 0's.
 *
 * ! You must do it in place.
 *
 * ! A straightforward solution using O(mn) space is probably a bad idea.
 *
 * ! A simple improvement uses O(m + n) space, but still not the best solution.
 *
 * ! Could you devise a constant space solution?
 */

class Solution
{
public:
    void setZeroes(std::vector<std::vector<int>>& matrix)
    {
        if (matrix.empty())
            return;

        const auto m = matrix.size();
        const auto n = matrix[0].size();
        // approach 1: time O(mn), space O(m+n)
        // - two hash sets storing row and column indicies, respectively
        // std::unordered_set<int> rows;
        // std::unordered_set<int> cols;
        // for (size_t i = 0; i < m; ++i) {
        //     for (size_t j = 0; j < n; ++j) {
        //         if (matrix[i][j] == 0) {
        //             rows.insert(i);
        //             cols.insert(j);
        //         }
        //     }
        // }
        // for (size_t i = 0; i < m; ++i) {
        //     for (size_t j = 0; j < n; ++j) {
        //         if (rows.count(i) || cols.count(j)) {
        //             matrix[i][j] = 0;
        //         }
        //     }
        // }
        // approach 2: time O(mn), space O(1)
        // - use the first row and the first column as indicators
        bool firstRowHasZero = false;
        bool firstColHasZero = false;
        for (size_t i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) {
                firstColHasZero = true;
                break;
            }
        }
        for (size_t j = 0; j < n; ++j) {
            if (matrix[0][j] == 0) {
                firstRowHasZero = true;
                break;
            }
        }
        // check inner area, row[1:end] and col[1:end]
        // - if matrix[i][j] = 0, update related flags
        for (size_t i = 1; i < m; ++i) {
            for (size_t j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        // according to the flags, update inner area
        for (size_t i = 1; i < m; ++i) {
            for (size_t j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        // finally, check the first row and the first column
        if (firstColHasZero) {
            for (size_t i = 0; i < m; ++i) {
                matrix[i][0] = 0;
            }
        }
        if (firstRowHasZero) {
            for (size_t j = 0; j < n; ++j) {
                matrix[0][j] = 0;
            }
        }
    }
};