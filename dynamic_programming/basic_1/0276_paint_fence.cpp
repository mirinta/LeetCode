#include <vector>

/**
 * You are painting a fence of "n" posts with "k" different colors. You must paint the posts
 * following these rules:
 *
 * - Every post must be painted exactly one color.
 *
 * - There cannot be three or more consecutive posts with the same color.
 *
 * Given the two integers "n" and "k", return the number of ways you can paint the fence.
 *
 * ! 1 <= n <= 50
 * ! 1 <= k <= 10^5
 */

class Solution
{
public:
    int numWays(int n, int k)
    {
        if (n < 1 || k < 1)
            return 0;

        if (n == 1)
            return k;

        if (n == 2)
            return k * k;

        // approach 1: 2D DP
        // - dp[i][j]
        // - j is either 0 or 1
        // - dp[i][0] = ways of painting i posts with k colors and the last two posts have different
        // color
        // - dp[i][1] = ways of painting i posts with k colors and the last two posts have the same
        // color
        // - i is 1-indexed, i in range [2, n], dp[0][...] and dp[1][...] are meaningless
        // base case: dp[2][0] and dp[2][1], only two posts
        // std::vector<std::vector<int>> dp(n + 1, std::vector<int>(2, 0));
        // dp[2][0] = k * (k - 1);
        // dp[2][1] = k;
        // for (int i = 3; i <= n; ++i) {
        //     dp[i][0] = (k - 1) * (dp[i - 1][0] + dp[i - 1][1]);
        //     dp[i][1] = dp[i - 1][0];
        // }
        // return dp[n][0] + dp[n][1];
        // approach 2: 1D DP
        int lastTwoSame = k;
        int lastTwoDiff = k * (k - 1);
        std::vector<int> dp(n + 1, 0);
        for (int i = 3; i <= n; ++i) {
            int diff = (k - 1) * (lastTwoSame + lastTwoDiff);
            int same = lastTwoDiff;
            lastTwoSame = same;
            lastTwoDiff = diff;
        }
        return lastTwoDiff + lastTwoSame;
    }
};