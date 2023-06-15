#include <vector>

/**
 * Given an integer "numRows", return the first numRows of Pascal's triangle.
 *
 * In Pascal's triangle, each number is the sum of the two number directly above it.
 *
 * ! 1 <= numRows <= 30
 */

class Solution
{
public:
    std::vector<std::vector<int>> generate(int numRows)
    {
        if (numRows <= 0)
            return {};

        // num of elements of ith row = i (1-indexed)
        std::vector<std::vector<int>> result;
        for (int i = 1; i <= numRows; ++i) {
            std::vector<int> row(i, 1);
            for (int j = 1; j < i - 1; ++j) {
                row[j] = result[i - 2][j - 1] + result[i - 2][j];
            }
            result.push_back(std::move(row));
        }
        return result;
    }
};