#include <vector>

/**
 * Given a positive integer "n", generate an "n x n" "matrix" filled with elements from "1" to "n^2"
 * in spiral order.
 */

class Solution
{
public:
    // similar to leet code 54
    std::vector<std::vector<int>> generateMatrix(int n)
    {
        if (n <= 0)
            return {};

        std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
        int left = 0;
        int right = n - 1;
        int top = 0;
        int bottom = n - 1;
        int val = 1;
        while (left <= right && top <= bottom) {
            // from left to right:
            for (int i = left; i <= right && top <= bottom; ++i) {
                result[top][i] = val++;
            }
            top++;
            // from top to bottom:
            for (int i = top; i <= bottom && left <= right; ++i) {
                result[i][right] = val++;
            }
            right--;
            // from right to left:
            for (int i = right; i >= left && top <= bottom; --i) {
                result[bottom][i] = val++;
            }
            bottom--;
            // from bottom to top:
            for (int i = bottom; i >= top && left <= right; --i) {
                result[i][left] = val++;
            }
            left++;
        }
        return result;
    }
};