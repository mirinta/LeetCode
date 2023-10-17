#include <vector>

/**
 * Given a binary array nums, you should delete one element from it.
 *
 * Return the size of the longest non-empty subarray containing only 1's in the resulting array.
 * Return 0 if there is no such subarray.
 *
 * ! 1 <= nums.length <= 10^5
 * ! nums[i] is either 0 or 1.
 */

class Solution
{
public:
    int longestSubarray(std::vector<int>& nums) { return approach3(nums); }

private:
    int approach3(std::vector<int>& nums)
    {
        // sliding window: time O(N), space O(1)
        // 0 X X X X 0
        //   ^       ^
        //   left    right
        int result = 0;
        for (int right = 0, left = 0, zeros = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) {
                zeros++;
            }
            while (zeros > 1) {
                if (nums[left] == 0) {
                    zeros--;
                }
                left++;
            }
            result = std::max(
                result, right - left); // not right - left + 1, because there's a deleted element
        }
        return result;
    }

    int approach2(std::vector<int>& nums)
    {
        // DP with space optimization: time O(N), space O(1)
        int withDeletion = 0;
        int withoutDeletion = nums[0];
        int result = 0;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == 1) {
                withoutDeletion += 1;
                withDeletion += 1;
            } else {
                withDeletion = withoutDeletion;
                withoutDeletion = 0;
            }
            result = std::max(result, withDeletion);
        }
        return result;
    }

    int approach1(std::vector<int>& nums)
    {
        // DP: time O(N), space O(N)
        // dp[i][0] = length of longest subarray of nums[0:i] without deletion
        // dp[i][1] = length of longest subarray of nums[0:i] wiht one deletion
        const int n = nums.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(2, 0));
        dp[0][0] = nums[0];
        int result = 0;
        for (int i = 1; i < n; ++i) {
            if (nums[i] == 1) {
                // X X X [1]
                dp[i][0] = 1 + dp[i - 1][0];
                dp[i][1] = 1 + dp[i - 1][1];
            } else {
                // X X X [0]
                dp[i][0] = 0; // it is no longer a subarray with consecutive 1's
                dp[i][1] = dp[i - 1][1];
            }
            // there must be one deletion (according to the problem)
            result = std::max(result, dp[i][1]);
        }
        return result;
    }
};