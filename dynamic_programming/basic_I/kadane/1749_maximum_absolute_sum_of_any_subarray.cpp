#include <array>
#include <vector>

/**
 * You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ...,
 * numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).
 *
 * Return the maximum absolute sum of any (possibly empty) subarray of nums.
 *
 * Note that abs(x) is defined as follows:
 *
 * - If x is a negative integer, then abs(x) = -x.
 *
 * - If x is a non-negative integer, then abs(x) = x.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 */

class Solution
{
public:
    int maxAbsoluteSum(std::vector<int>& nums) { return approach2(nums); }

private:
    // DP with space optimization, TC = O(N), SC = O(1)
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int max = 0;
        int min = 0;
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            max = std::max(nums[i - 1], max + nums[i - 1]);
            min = std::min(nums[i - 1], min + nums[i - 1]);
            result = std::max({result, std::abs(max), std::abs(min)});
        }
        return result;
    }

    // DP, TC = O(N), SC = O(N)
    int approach1(const std::vector<int>& nums)
    {
        // dp[i][0] = max sum of subarrays of nums[0:i-1] ending at nums[i-1]
        // dp[i][1] = min sum of subarrays of nums[0:i-1] ending at nums[i-1]
        const int n = nums.size();
        std::vector<std::array<int, 2>> dp(n + 1, {0, 0});
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::max(nums[i - 1], dp[i - 1][0] + nums[i - 1]);
            dp[i][1] = std::min(nums[i - 1], dp[i - 1][1] + nums[i - 1]);
            result = std::max({result, std::abs(dp[i][0]), std::abs(dp[i][1])});
        }
        return result;
    }
};