#include <array>
#include <vector>

/**
 * You are painting a fence of n posts with k different colors. You must paint the posts following
 * these rules:
 *
 * - Every post must be painted exactly one color.
 *
 * - There cannot be three or more consecutive posts with the same color.
 *
 * Given the two integers n and k, return the number of ways you can paint the fence.
 *
 * ! 1 <= n <= 50
 * ! 1 <= k <= 10^5
 * ! The test cases are generated such that the answer is in the range [0, 231 - 1] for the given n
 * ! and k.
 */

class Solution
{
public:
    int numWays(int n, int k) { return approach2(n, k); }

private:
    // DP with space optimization, time O(N), space O(1)
    int approach2(int n, int k)
    {
        if (n == 1)
            return k;

        int diff = k * (k - 1);
        int same = k;
        for (int i = 3; i <= n; ++i) {
            const int backup = diff;
            diff = (diff + same) * (k - 1);
            same = backup;
        }
        return diff + same;
    }

    // DP, time O(N), space O(N)
    int approach1(int n, int k)
    {
        if (n == 1)
            return k;

        // dp[i][0] = num of ways to paint posts[0:i) with k colors while the last two posts have
        // different colors
        // dp[i][1] = num of ways to paint posts[0:i) with k colors while the last two posts have
        // the same color
        std::vector<std::array<int, 2>> dp(n + 1, {0, 0});
        dp[2][0] = k * (k - 1);
        dp[2][1] = k;
        for (int i = 3; i <= n; ++i) {
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) * (k - 1); // Y X [!=X] or X X [!=X]
            dp[i][1] = dp[i - 1][0];                            // Y X [only X]
        }
        return dp[n][0] + dp[n][1];
    }
};
