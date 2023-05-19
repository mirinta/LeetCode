#include <vector>

/**
 * You are a professional robber planning to rob houses along a street. Each house has a certain
 * amount of money stashed. All houses at this place are arranged in a circle. That means the first
 * house is the neighbor of the last one. Meanwhile, adjacent houses have a security system
 * connected, and it will automatically contact the police if two adjacent houses were broken into
 * on the same night.
 *
 * Given an integer array "nums" representing the amount of money of each house, return the maximum
 * amount of money you can rob tonight without alerting the police.
 *
 * ! nums[i] >= 0
 */

class Solution
{
public:
    int rob(std::vector<int>& nums)
    {
        // house range is either house[0:n-2] or house[1:n-1]
        if (nums.empty())
            return 0;

        if (nums.size() == 1)
            return nums[0];

        return std::max(rob(0, nums.size() - 2, nums), rob(1, nums.size() - 1, nums));
    }

private:
    // max value of robbing house[start, end], similar to LC 198
    int rob(int start, int end, const std::vector<int>& nums)
    {
        if (start < 0 || start >= nums.size())
            return 0;

        if (end < 0 || end >= nums.size())
            return 0;

        if (start == end)
            return nums[start];

        // dp[i] = max value of robbing house[i:end]
        const auto n = end - start + 1;
        std::vector<int> dp(n);
        // base cases:
        dp[n - 1] = nums[end];
        dp[n - 2] = std::max(nums[end], nums[end - 1]);
        for (int i = n - 3; i >= 0; --i) {
            dp[i] = std::max(nums[i + start] + dp[i + 2], dp[i + 1]);
        }
        return dp[0];
    }
};