#include <vector>

/**
 * Given an integer n, break it into the sum of k positive integers, where k >= 2, and maximize the
 * product of those integers.
 *
 * Return the maximum product you can get.
 *
 * ! 2 <= n <= 58
 */

class Solution
{
public:
    int integerBreak(int n)
    {
        if (n < 2)
            return 0;

        // cut a ruler: 0 1 ... i i + 1 ... n into at least two parts
        // dp[i] = max product of cutting a ruler with length n
        std::vector<int> dp(n + 1, 0);
        dp[1] = 0;
        dp[2] = 1;
        for (int i = 3; i <= n; ++i) {
            for (int cut = 1; cut <= i / 2; ++cut) {
                // 0 1 ... [cut] cut+1 ... i
                // choose a cutting position at "cut",
                // the ruler is cut into two parts:
                // - [0...cut], length = cut
                // - [cut+1...i], length = i-cut
                // stop cutting or continue to cut the remaining part?
                dp[i] = std::max({dp[i], cut * (i - cut), cut * dp[i - cut]});
            }
        }
        return dp[n];
    }
};