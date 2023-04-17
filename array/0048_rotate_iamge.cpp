#include <vector>

/**
 * You are given an "nxn" 2D "matrix" representing an image, rotate the image by 90 degrees
 * (clockwise).
 *
 * You have to rotate the image in-place, which means you have to modify the input 2D matrix
 * directly. DO NOT allocate another 2D matrix and do the rotation.
 */

class Solution
{
public:
    // for a 4x4 matrix:
    // 1  2  3             7  4  1                   1  4  7
    // 4  5  6  -ROTATE->  8  5  2 -REVERSE (rows)-> 2  5  8
    // 7  8  9             9  6  3                   3  6  9
    //    |                                             |
    //    |<----------------TRANSPOSE------------------>|
    //
    // - clockwise rotate 90 degrees: transpose (main diagonal) + reverse
    // - counter-clockwise rotate 90 degrees: transpose (anti-diagonal) + reverse
    void rotate(std::vector<std::vector<int>>& matrix)
    {
        if (matrix.empty())
            return;

        const auto rows = matrix.size();
        const auto cols = matrix[0].size();
        if (cols == 0)
            return;

        // transpose
        for (size_t i = 0; i < rows; ++i) {
            // notice the range of "j"
            for (size_t j = i; j < cols; ++j) {
                std::swap(matrix[i][j], matrix[j][i]);
            }
        }
        // reverse each row
        for (auto& vec : matrix) {
            size_t forward = 0;
            size_t backward = vec.size() - 1;
            while (forward < backward) {
                std::swap(vec[forward++], vec[backward--]);
            }
        }
    }
};