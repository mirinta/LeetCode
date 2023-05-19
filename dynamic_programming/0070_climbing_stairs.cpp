#include <utility>

/**
 * You are climbing a staircase. It takes "n" steps to reach the top.
 *
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 */

class Solution
{
public:
    int climbStairs(int n)
    {
        if (n < 1)
            return 0;

        if (n == 1)
            return 1;

        // approach 1: 1D array DP
        // dp[i] = distinct ways of climbing i steps to reach the top
        // std::vector<int> dp(n + 1, 0);
        // dp[1] = 1;
        // dp[2] = 2;
        // for (int i = 3; i <= n; ++i) {
        //     dp[i] = dp[i - 1] + dp[i - 2];
        // }
        // return dp[n];

        // approach 2:
        // we see that dp[i] is only dependent on dp[i-1] and dp[i-2],
        // instead of using an array, we can only maintain these two values
        int dp_2 = 1; // dp(n-2)
        int dp_1 = 2; // dp(n-1)
        for (int i = 3; i <= n; ++i) {
            // prepare for the next round:
            // dp(n+1) = dp(n) + dp(n-1),
            // dp_1 = dp(n), dp_2 = dp(n-1)
            std::swap(dp_1, dp_2);
            dp_1 += dp_2;
        }
        return dp_1;
    }
};