#include <vector>

/**
 * Given an "mxn" "matrix", return all elements of the matrix in spiral order.
 */

class Solution
{
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix)
    {
        if (matrix.empty())
            return {};

        const auto rows = matrix.size();
        const auto cols = matrix[0].size();
        if (cols == 0)
            return {};

        std::vector<int> result(rows * cols, 0);

        return result;
    }
};