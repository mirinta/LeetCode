#include <vector>

/**
 * You have n dice, and each die has k faces numbered from 1 to k.
 *
 * Given three integers n, k, and target, return the number of possible ways (out of the kn total
 * ways) to roll the dice, so the sum of the face-up numbers equals target. Since the answer may be
 * too large, return it modulo 10^9 + 7.
 *
 * ! 1 <= n, k <= 30
 * ! 1 <= target <= 1000
 */

class Solution
{
public:
    int numRollsToTarget(int n, int k, int target)
    {
        constexpr int kMod = 1e9 + 7;
        // dp[i][t] = num of ways to make up t using exactly i dices and each dice has k faces
        // - t is in the range of [1*i, min(target,k*i)]
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(target + 1, 0));
        dp[0][0] = 1; // base case
        for (int i = 1; i <= n; ++i) {
            for (int t = i; t <= std::min(target, k * i); ++t) {
                for (int val = 1; val <= std::min(t, k); ++val) {
                    dp[i][t] = (dp[i][t] + dp[i - 1][t - val]) % kMod;
                }
            }
        }
        return dp[n][target];
    }
};