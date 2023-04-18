#include <vector>

/**
 * Given an "mxn" "matrix", return all elements of the matrix in spiral order.
 */

class Solution
{
public:
    // for a 3x3 matrix:
    //            ------------ top bound
    //            | 1  2  3  |
    // left bound | 8  9  4  | right bound
    //            | 7  6  5  |
    //            ------------ bottom bound
    // - initial values: left = 0, right = columns, top = 0, bottom = rows
    // - from left to right, matrix[top][i], i in [left, right], then top++
    // - from top to bottom, matrix[i][right], i in [top, bottom], then right--
    // - from right to left, matrix[bottom][i], i in [right, left], then bottom--
    // - from bottom to top, matrix[i][left], i in [bottom, top], then left++
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix)
    {
        if (matrix.empty())
            return {};

        const auto rows = matrix.size();
        const auto cols = matrix[0].size();
        if (cols == 0)
            return {};

        std::vector<int> result{};
        result.reserve(rows * cols);
        int left = 0;
        int right = cols - 1;
        int top = 0;
        int bottom = rows - 1;
        while (left <= right && top <= bottom) {
            // from left to right
            for (int i = left; i <= right && top <= bottom; ++i) {
                result.push_back(matrix[top][i]);
            }
            top++;
            // from top to bottom
            for (int i = top; i <= bottom && left <= right; ++i) {
                result.push_back(matrix[i][right]);
            }
            right--;
            // from right to left
            for (int i = right; i >= left && top <= bottom; --i) {
                result.push_back(matrix[bottom][i]);
            }
            bottom--;
            // from bottom to top
            for (int i = bottom; i >= top && left <= right; --i) {
                result.push_back(matrix[i][left]);
            }
            left++;
        }
        return result;
    }
};