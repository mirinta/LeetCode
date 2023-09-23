#include <vector>

/**
 * Given an integer n, return the least number of perfect square numbers that sum to n.
 *
 * A perfect square is an integer that is the square of an integer; in other words, it is the
 * product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and
 * 11 are not.
 *
 * ! 1 <= n <= 104
 */

class Solution
{
public:
    int numSquares(int n)
    {
        // dp[i] = least num of perfect square numbers that sum to i
        // base case:
        // - dp[0] = 0
        // - if i is a perfect square, then dp[i] = 1 is already the optimal answer
        // - otherwise, let dp[i] = i, because i is the sum of i 1's
        std::vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i * i <= n; ++i) {
            dp[i * i] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            if (dp[i] == 1)
                continue;

            for (int j = 1; j * j <= i; ++j) {
                dp[i] = std::min(dp[i], 1 + dp[i - j * j]);
            }
        }
        return dp[n];
    }
};