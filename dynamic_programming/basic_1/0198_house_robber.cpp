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
    int rob(const std::vector<int>& nums) { return approach3(nums); }

private:
    int approach1(const std::vector<int>& nums)
    {
        if (nums.empty())
            return 0;

        // dp[i][0] = max value of robbing nums[0:i) while the ith house is not robbed
        // dp[i][1] = max value of robbing nums[0:i) while the ith house is robbed
        const auto n = nums.size();
        std::vector<std::pair<int, int>> dp(n + 1, {0, 0});
        for (int i = 1; i <= n; ++i) {
            dp[i].first = std::max(dp[i - 1].first, dp[i - 1].second);
            dp[i].second = dp[i - 1].first + nums[i - 1];
        }
        return std::max(dp[n].first, dp[n].second);
    }

    int approach2(const std::vector<int>& nums)
    {
        if (nums.empty())
            return 0;

        // dp[i] = max value of robbing nums[i:n)
        const auto n = nums.size();
        std::vector<int> dp(n + 1, 0);
        dp[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            dp[i] = std::max(dp[i + 1], nums[i] + dp[i + 2]);
        }
        return dp[0];
    }

    int approach3(const std::vector<int>& nums)
    {
        // optimize approach2
        if (nums.empty())
            return 0;

        const auto n = nums.size();
        int robNext = nums[n - 1];
        int robNextPlusOne = 0;
        for (int i = n - 2; i >= 0; --i) {
            int thisRound = std::max(robNext, nums[i] + robNextPlusOne);
            robNextPlusOne = robNext;
            robNext = thisRound;
        }
        return robNext;
    }
};
