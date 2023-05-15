#include <vector>

/**
 * Given an integer array "nums", find the sub-array with the largest sum, and return its sum.
 *
 * Example:
 * Input: nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
 * Output: 6
 * Explanation: The sub-array [4, -1, 2, 1] has the largest sum 6.
 */

class Solution
{
public:
    int maxSubArray(std::vector<int>& nums)
    {
        if (nums.empty())
            return INT_MIN;

        // approach 1: sliding window
        // - expand window if sum of values within window >= 0
        // - otherwise, shrink window
        // int result = INT_MIN;
        // int left = 0;
        // int right = 0;
        // int windowSum = 0;
        // while (right < nums.size()) {
        //     windowSum += nums[right++];
        //     result = std::max(windowSum, result);
        //     while (windowSum < 0) {
        //         windowSum -= nums[left++];
        //     }
        // }
        // return result;
        // ------------------------------
        // approach 2:
        // int result = INT_MIN;
        // int sum = 0;
        // for (const auto& val : nums) {
        //     sum += val;
        //     if (sum > result) {
        //         result = sum;
        //     }
        //     if (sum < 0) {
        //         sum = 0;
        //     }
        // }
        // return result;
        // ------------------------------
        // approach 3: DP
        // dp[i] = max sum of subarray that ends with nums[i]
        // base case: the subarray that ends with nums[0] is {nums[0]}
        // const auto n = nums.size();
        // std::vector<int> dp(n, 0);
        // dp[0] = nums[0];
        // for (int i = 1; i < n; ++i) {
        //     dp[i] = std::max(nums[i], dp[i - 1] + nums[i]);
        // }
        // int result = INT_MIN;
        // for (const auto& val : dp) {
        //     result = std::max(result, val);
        // }
        // return result;
        // ------------------------------
        // approach 4: in approach 3, dp[i] is only dependent on dp[i - 1]
        // thus, we only need two variables to record these two states
        // int dp0 = nums[0];
        // int dp1 = 0;
        // int result = dp0;
        // for (int i = 1; i < nums.size(); ++i) {
        //     dp1 = std::max(nums[i], dp0 + nums[i]);
        //     dp0 = dp1;
        //     result = std::max(result, dp1);
        // }
        // return result;
        // ------------------------------
        // approach 5: prefix
        // preSum[i] = sum(nums[0], ..., nums[i - 1])
        // then preSum[i + 1] - preSum[j] = sum(nums[j], ..., nums[i])
        const auto n = nums.size();
        std::vector<int> preSum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            preSum[i] = preSum[i - 1] + nums[i - 1];
        }
        int result = INT_MIN;
        int minPreSum = INT_MAX;
        // as shown above, we want to access preSum[i + 1]
        // thus we need to iterate i from 0 to n - 1
        for (int i = 0; i < n; ++i) {
            minPreSum = std::min(minPreSum, preSum[i]);
            result = std::max(result, preSum[i + 1] - minPreSum);
        }
        return result;
    }
};