#include <vector>

/**
 * Given an integer array nums, find a subarray that has the largest product, and return the
 * product.
 *
 * The test cases are generated so that the answer will fit in a 32-bit integer.
 *
 * ! 1 <= nums.length <= 2 * 10^4
 * ! -10 <= nums[i] <= 10
 * ! The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 */

class Solution
{
public:
    int maxProduct(std::vector<int>& nums) { return approach2(nums); }

private:
    // DP with space optimization, time O(N), space O(1)
    int approach2(const std::vector<int>& nums)
    {
        int prevMax = nums[0];
        int prevMin = nums[0];
        int result = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            const int product1 = prevMax * nums[i];
            const int product2 = prevMin * nums[i];
            prevMax = std::max({nums[i], product1, product2});
            prevMin = std::min({nums[i], product1, product2});
            result = std::max({result, prevMax, prevMin});
        }
        return result;
    }

    // DP, time O(N), space O(N)
    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i].first = max product of subarrays that end with nums[i]
        // dp[i].second = min product of subarrays that end with nums[i]
        std::vector<std::pair<int, int>> dp(n, {INT_MIN, INT_MAX});
        dp[0] = {nums[0], nums[0]};
        int result = nums[0];
        for (int i = 1; i < n; ++i) {
            const auto& [prevMax, prevMin] = dp[i - 1];
            const int product1 = prevMax * nums[i];
            const int product2 = prevMin * nums[i];
            dp[i].first = std::max({nums[i], product1, product2});
            dp[i].second = std::min({nums[i], product1, product2});
            result = std::max({result, dp[i].first, dp[i].second});
        }
        return result;
    }
};