#include <vector>

/**
 * You are climbing a staircase. It takes "n" steps to reach the top.
 *
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 *
 * ! 1 <= n <= 45
 */

class Solution
{
public:
    int climbStairs(int n) { return approach2(n); }

private:
    // Fibonacci, time O(N), space O(1)
    int approach2(int n)
    {
        if (n <= 1)
            return 1;

        int iMinus2 = 1;
        int iMinus1 = 1;
        int result = 0;
        for (int i = 2; i <= n; ++i) {
            result = iMinus1 + iMinus2;
            iMinus2 = iMinus1;
            iMinus1 = result;
        }
        return result;
    }

    // DP, time O(N), space O(N)
    int approach1(int n)
    {
        // 0 1 2 ... X ... n
        // dp[i] = num of ways to climb a staircase with n steps
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};