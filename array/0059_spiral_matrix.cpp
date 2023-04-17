#include <vector>

/**
 * Given a positive integer "n", generate an "n x n" "matrix" filled with elements from "1" to "n^2"
 * in spiral order.
 */

class Solution
{
public:
    std::vector<std::vector<int>> generateMatrix(int n)
    {
        if (n <= 0)
            return {};

        if (n == 1)
            return {{1}};

        std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

        return result;
    }
};