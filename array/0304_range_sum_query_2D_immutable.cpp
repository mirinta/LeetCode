#include <vector>

/**
 * Given a 2D matrix "matrix", handle multiple queries of the following type:
 *
 * - Calculate the sum of the elements of "matrix" inside the rectangle defined by its upper left
 * corner "(row1, col1)" and lower right corner "(row2, col2)".
 *
 * Implement the "NumMatrix" class:
 *
 * - "NumMatrix(int[][] matrix)" initializes the object with the integer matrix "matrix".
 *
 * - "int sumRegion(int row1, int col1, int row2, int col2)" returns the sum of the elements of
 * "matrix" inside the rectangle defined by its upper left corner "(row1, col1)" and lower right
 * corner "(row2, col2)".
 *
 * You must design an algorithm where "sumRegion" works on O(1) time complexity.
 */

class NumMatrix
{
public:
    NumMatrix(std::vector<std::vector<int>>& matrix)
        : _preSums(matrix.size(), std::vector<int>(matrix[0].size(), 0))
    {
    }

    int sumRegion(int row1, int col1, int row2, int col2) {}

private:
    std::vector<std::vector<int>> _preSums;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */