#include <vector>

/**
 * Given an integer n, return the least number of perfect square numbers that sum to n.
 *
 * A perfect square is an integer that is the square of an integer; in other words, it is the
 * product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and
 * 11 are not.
 *
 * Example:
 * Input: n = 13
 * Output: 2
 * Explanation: 13 = 4 + 9
 */

class Solution
{
public:
    int numSquares(int n)
    {
        if (n < 1)
            return 0;

        // knapsack capacity = n
        // packages are 1, 4, 9, ..., j^2, where j^2 <= n
        // problem: min number of packages to fill the knapsack
        std::vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            dp[i] = i;
            for (int j = 1; j * j <= i; ++j) {
                dp[i] = std::min(dp[i], 1 + dp[i - j * j]);
            }
        }
        return dp[n];
    }
};