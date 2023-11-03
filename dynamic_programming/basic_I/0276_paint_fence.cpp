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
 * ! The testcases are generated such that the answer is in the range [0, 231 - 1] for the given n
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
        if (n <= 2)
            return n == 1 ? k : k * k;

        int lastTwoDiffColor = k * (k - 1);
        int lastTwoSameColor = k;
        for (int i = 3; i <= n; ++i) {
            const auto backup = lastTwoDiffColor;
            lastTwoDiffColor = (k - 1) * (lastTwoDiffColor + lastTwoSameColor);
            lastTwoSameColor = backup;
        }
        return lastTwoDiffColor + lastTwoSameColor;
    }

    // DP, time O(N), space O(N)
    int approach1(int n, int k)
    {
        if (n <= 2)
            return n == 1 ? k : k * k;

        // dp[i][0] = num of ways to paint i posts with k colors while the last two posts have
        // different colors 
        // dp[i][1] = num of ways to paint i posts with k colors while the last two posts have the 
        // same color
        std::vector<std::array<int, 2>> dp(1 + n, {0, 0});
        dp[2][0] = k * (k - 1);
        dp[2][1] = k;
        for (int i = 3; i <= n; ++i) {
            dp[i][0] = (k - 1) * (dp[i - 1][0] + dp[i - 1][1]);
            dp[i][1] = dp[i - 1][0];
        }
        return dp[n][0] + dp[n][1];
    }
};
