#include <climits>
#include <vector>

/**
 * Given an "n x n" array of integers "matrix", return the minimum sum of any falling path through
 * "matrix".
 *
 * A falling path starts at any element in the first row and chooses the element in the next row
 * that is either directly below or diagonally left/right. Specially, the next element from position
 * (row, col) will be (row + 1, col - 1), (row + 1, col), and (row + 1, col + 1).
 *
 * Example:
 * [ 2   #1#   3 ]  [ 2   #1#   3 ]
 * [ 6   #5#   4 ]  [ 6    5   #4#]
 * [#7#   8    9 ]  [ 7   #8#   9 ]
 *
 * There are two falling paths with a minimum sum (13): 1->5->7 and 1->4->8.
 */

class Solution
{
public:
    int minFallingPathSum(std::vector<std::vector<int>>& matrix)
    {
        const auto n = matrix.size();
        // dp[i][j] = the minimum sum of falling path from position (0, ...) to position (i, j)
        // There are three source positions that can fall to (i, j),
        // so dp[i][j] = val[i][j] + min(dp[i - 1][j], dp[i - 1][j + 1], dp[i - 1][j - 1])
        // The above equation is only dependent on the previous row,
        // so it's not necessary to make a new DP matrix, we can directly solve the problem
        // in-place. The loop begins from the second row, because the first row needs to remain the
        // same.
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0)
                    continue;

                auto val = matrix[i - 1][j];
                if (j - 1 >= 0) {
                    val = std::min(val, matrix[i - 1][j - 1]);
                }
                if (j + 1 < n) {
                    val = std::min(val, matrix[i - 1][j + 1]);
                }
                matrix[i][j] += val;
            }
        }
        int result = INT_MAX;
        for (const auto& v : matrix[n - 1]) {
            if (v < result) {
                result = v;
            }
        }
        return result;
    }
};