#include <vector>

/**
 * You are a professional robber planning to rob houses along a street. Each house has a certain
 * amount of money stashed, the only constraint stopping you from robbing each of them is that
 * adjacent houses have security systems connected and it will automatically contact the police if
 * two adjacent houses were broken into on the same night.
 *
 * Given an integer array "nums" representing the amount of money of each house, return the maximum
 * amount of money you can rob tonight without alerting the police.
 *
 * ! 1 <= nums.length <= 100
 * ! 0 <= nums[i] <= 400
 */

class Solution
{
public:
    int rob(std::vector<int>& nums) { return approach2(nums); }

private:
    // DP with space optimization, time O(N), space O(1)
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int rob = INT_MIN;
        int notRob = 0;
        for (int i = 1; i <= n; ++i) {
            const int backup = notRob;
            notRob = std::max(notRob, rob);
            rob = backup + nums[i - 1];
        }
        return std::max(rob, notRob);
    }

    // DP, time O(N), space O(N)
    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i][0] = max profit of robbing the first i house, and the ith house is not robbed
        // dp[i][1] = max profit of robbing the first i house, and the ith house is robbed
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(2, 0));
        dp[0][1] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = dp[i - 1][0] + nums[i - 1];
        }
        return std::max(dp[n][0], dp[n][1]);
    }
};