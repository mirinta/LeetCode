#include <array>
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
    // DP with space optimization, TC = O(N), SC = O(1)
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int max = 1;
        int min = 1;
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            const int backup = min;
            min = std::min({nums[i], nums[i] * min, nums[i] * max});
            max = std::max({nums[i], nums[i] * backup, nums[i] * max});
            result = std::max(result, max);
        }
        return result;
    }

    // DP, TC = O(N), SC = O(N)
    int approach1(const std::vector<int>& nums)
    {
        // dp[i][0] = min subarray product of nums[0:i-1] endint at nums[i-1]
        // dp[i][1] = max subarray product of nums[0:i-1] ending at nums[i-1]
        const int n = nums.size();
        std::vector<std::array<int, 2>> dp(n + 1);
        dp[0] = {1, 1};
        int result = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] =
                std::min({nums[i - 1], nums[i - 1] * dp[i - 1][0], nums[i - 1] * dp[i - 1][1]});
            dp[i][1] =
                std::max({nums[i - 1], nums[i - 1] * dp[i - 1][0], nums[i - 1] * dp[i - 1][1]});
            result = std::max(result, dp[i][1]);
        }
        return result;
    }
};