#include <vector>

/**
 * You are given an integer array nums of length n and a positive integer k.
 *
 * The power of an array of integers is defined as the number of subsequences with their sum equal
 * to k.
 *
 * Return the sum of power of all subsequences of nums.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= n <= 100
 * ! 1 <= nums[i] <= 10^4
 * ! 1 <= k <= 100
 */

class Solution
{
public:
    int sumOfPower(std::vector<int>& nums, int k)
    {
        // dp[i][j] = sum of power of all subsequences of nums[0:i-1] with sum equal to j
        constexpr int kMod = 1e9 + 7;
        const int n = nums.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                dp[i][j] = 2 * dp[i - 1][j] % kMod;
                if (j >= nums[i - 1]) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - nums[i - 1]]) % kMod;
                }
            }
        }
        return dp[n][k];
    }
};