#include <vector>

/**
 * You are given an integer array nums. You are initially positioned at the array's first index, and
 * each element in the array represents your maximum jump length at that position.
 *
 * Return true if you can reach the last index, or false otherwise.
 *
 * ! 1 <= nums.length <= 10^4
 * ! 0 <= nums[i] <= 10^5
 */

class Solution
{
public:
    bool canJump(std::vector<int>& nums) { return approach2(nums); }

private:
    // Greedy, time O(N), space O(1)
    bool approach2(const std::vector<int>& nums)
    {
        int furthest = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (i > furthest)
                return false;

            furthest = std::max(furthest, i + nums[i]);
        }
        return furthest >= nums.size() - 1;
    }

    // DP, time O(N^2), space O(N)
    bool approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<bool> dp(n, false);
        dp[n - 1] = true;
        for (int i = n - 2; i >= 0; --i) {
            for (int steps = std::min(nums[i], n - i - 1); steps > 0; --steps) {
                if (dp[i + steps]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[0];
    }
};
