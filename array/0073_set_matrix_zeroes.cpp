#include <unordered_set>
#include <vector>

/**
 * Given an m x n integer matrix, if an element is 0, ste its entire row and column to 0's.
 *
 * ! m == matrix.length
 * ! n == matrix[0].length
 * ! 1 <= m, n <= 200
 * ! -231 <= matrix[i][j] <= 231 - 1
 *
 * ! You must do it in place.
 * ! A straightforward solution using O(mn) space is probably a bad idea.
 * ! A simple improvement uses O(m + n) space, but still not the best solution.
 * ! Could you devise a constant space solution?
 */

class Solution
{
public:
    void setZeroes(std::vector<std::vector<int>>& matrix) { approach2(matrix); }

private:
    // time O(MN), space O(1)
    void approach2(std::vector<std::vector<int>>& matrix)
    {
        // use the first row and the first column to
        // indicate whether a row or a column needs to be set to 0's
        const int m = matrix.size();
        const int n = matrix[0].size();
        bool firstRowHasZero = false;
        bool firstColHasZero = false;
        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == 0) {
                firstRowHasZero = true;
                break;
            }
        }
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) {
                firstColHasZero = true;
                break;
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        for (int j = 0; j < n && firstRowHasZero; ++j) {
            matrix[0][j] = 0;
        }
        for (int i = 0; i < m && firstColHasZero; ++i) {
            matrix[i][0] = 0;
        }
    }

    // time O(MN), space O(M+N)
    void approach1(std::vector<std::vector<int>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::unordered_set<int> rows;
        std::unordered_set<int> cols;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    rows.insert(i);
                    cols.insert(j);
                }
            }
        }
        for (const auto& i : rows) {
            std::fill(matrix[i].begin(), matrix[i].end(), 0);
        }
        for (const auto& j : cols) {
            for (int i = 0; i < m; ++i) {
                matrix[i][j] = 0;
            }
        }
    }
};