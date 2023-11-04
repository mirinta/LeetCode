#include <vector>

/**
 * You are given a 0-indexed array of integers nums, and an integer target.
 *
 * Return the length of the longest subsequence of nums that sums up to target. If no such
 * subsequence exists, return -1.
 *
 * A subsequence is an array that can be derived from another array by deleting some or no elements
 * without changing the order of the remaining elements.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 1000
 * ! 1 <= target <= 1000
 */

class Solution
{
public:
    int lengthOfLongestSubsequence(std::vector<int>& nums, int target)
    {
        return approach2(nums, target);
    }

private:
    // DP with space optimization, O(target*N), space O(target)
    int approach2(const std::vector<int>& nums, int target)
    {
        const int n = nums.size();
        std::vector<int> dp(1 + target, -1);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = target; j >= 1; --j) {
                if (j - nums[i - 1] >= 0 && dp[j - nums[i - 1]] != -1) {
                    dp[j] = std::max(dp[j], 1 + dp[j - nums[i - 1]]);
                }
            }
        }
        return dp[target];
    }

    // DP, time O(target*N), space O(target*N)
    int approach1(const std::vector<int>& nums, int target)
    {
        const int n = nums.size();
        // dp[i][j] = length of the longest subsequence of nums[0:i) that sums up to j
        std::vector<std::vector<int>> dp(1 + n, std::vector<int>(1 + target, -1));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= target; ++j) {
                if (j - nums[i - 1] >= 0 && dp[i - 1][j - nums[i - 1]] != -1) {
                    dp[i][j] = std::max(dp[i - 1][j], 1 + dp[i - 1][j - nums[i - 1]]);
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][target];
    }
};