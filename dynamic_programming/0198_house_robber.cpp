#include <vector>

/**
 * You are a professional robber planning to rob houses along a street. Each house has a certain
 * amount of money stashed, the only constraint stopping you from robbing each of them is that
 * adjacent houses have security systems connected and it will automatically contact the police if
 * two adjacent houses were broken into on the same night.
 *
 * Given an integer array "nums" representing the amount of money of each house, return the maximum
 * amount of money you can rob tonight without alerting the police.
 */

class Solution
{
public:
    int rob(std::vector<int>& nums)
    {
        const auto n = nums.size();
        if (n < 1)
            return 0;

        if (n == 1)
            return nums[0];

        // dp[i] = max value of robbing house[i:n-1]
        // why not dp[i] = max value of robbing house[0:i)?
        // - standing at the ith house, dp[i-1] is the max value of robbing the first i-1 houses
        // - we don't know whether the (i-1)th house is robbed, so the decision can't be made
        std::vector<int> dp(n, 0);
        // base cases:
        // - i = n-1, only one house in house[i:n-1]
        // - i = n-2, two houses in house[i:n-1], choose the one with max value
        dp[n - 1] = nums[n - 1];
        dp[n - 2] = std::max(nums[n - 2], nums[n - 1]);
        for (int i = n - 3; i >= 0; --i) {
            dp[i] = std::max(dp[i + 2] + nums[i], dp[i + 1]);
        }
        return dp[0];
    }
};