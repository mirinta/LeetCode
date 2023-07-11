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

        // here, we consider n >= 5
        // cut it into pieces with length 3, as much as possible
        // #NOTE#, if length = 4, we cut it into 2 and 2, it is better than 1 and 3
        // cut the remaining part into pieces with length 2, as much as possible
        int numOf3 = n / 3;
        if (n % 3 == 1) {
            numOf3--;
        }
        int numOf2 = (n - numOf3 * 3) / 2;
        return std::pow(3, numOf3) * std::pow(2, numOf2);
    }
};
