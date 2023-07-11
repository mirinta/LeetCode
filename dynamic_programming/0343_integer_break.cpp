#include <cmath>
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
    int integerBreak(int n) { return approach2(n); }

private:
    // approach1: DP
    int approach1(int n)
    {
        if (n < 2)
            return 0;

        // cut a ruler: 0 1 ... i i + 1 ... n into at least two parts
        // dp[i] = max product of cutting a ruler with length n
        // - base cases: dp[0] = dp[1] = 0, dp[2] = 1
        std::vector<int> dp(n + 1, 0);
        dp[2] = 1;
        for (int i = 3; i <= n; ++i) {
            for (int cut = 1; cut <= i / 2; ++cut) {
                // 0 1 ... [cut] ... n
                // choose a cutting position at "cut",
                // the ruler is cut into two parts:
                // - [0...cut], length = cut
                // - [cut...i], length = i-cut
                // choices = {stop cutting, continue to cut the remaining part}
                dp[i] = std::max({dp[i], cut * (i - cut), cut * dp[i - cut]});
            }
        }
        return dp[n];
    }

    // approach2: Greedy
    int approach2(int n)
    {
        if (n < 2)
            return 0;

        if (n == 2)
            return 1; // 1x1

        if (n == 3)
            return 2; // 1x2

        if (n == 4)
            return 4; // 2x2

        // consider n >= 5
        // - cut it into pieces with length 3, as much as possible
        // - #NOTE#, if length <= 4, we don't cut the rope
        constexpr int kMod = 1e9 + 7;
        long long result = 1;
        while (n > 4) {
            result = result * 3 % kMod;
            n -= 3;
        }
        result = result * n % kMod;
        return result;
    }
};
