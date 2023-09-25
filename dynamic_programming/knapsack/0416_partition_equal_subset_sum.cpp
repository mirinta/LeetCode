#include <numeric>
#include <vector>

/**
 * Given an integer array "nums", return true if you can partition the array into two subsets such
 * that the sum of the elements in both subsets is equal or false otherwise.
 *
 * ! 1 <= nums.length <= 200
 * ! 1 <= nums[i] <= 100
 */

class Solution
{
public:
    bool canPartition(std::vector<int>& nums) { return approach2(nums); }

private:
    // DP with space optimization, time O(MN), space O(M)
    // - N is the number of nums, and M is the half sum of nums
    bool approach2(const std::vector<int>& nums)
    {
        const int totalSum = std::accumulate(nums.begin(), nums.end(), 0);
        if (totalSum % 2 != 0)
            return false;

        const int target = totalSum / 2;
        const int n = nums.size();
        std::vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int i = 1; i <= n; ++i) {
            for (int j = target; j >= 1; --j) {
                const int diff = j - nums[i - 1];
                if (diff >= 0) {
                    dp[j] = dp[j] || dp[diff];
                }
            }
        }
        return dp[target];
    }

    // DP, time O(MN), space O(MN)
    // - N is the number of nums, and M is the half sum of nums
    bool approach1(const std::vector<int>& nums)
    {
        const int totalSum = std::accumulate(nums.begin(), nums.end(), 0);
        if (totalSum % 2 != 0)
            return false;

        const int target = totalSum / 2;
        const int n = nums.size();
        // dp[i][j] = is it possible to make up amount j using nums[0:i)
        // base case:
        // - dp[0][0] = true
        // - dp[i][0] = true
        // - dp[0][j] = false
        std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1, false));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = true;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= target; ++j) {
                const int diff = j - nums[i - 1]; // nums[i] > 0, it means diff < j
                if (diff < 0) {
                    dp[i][j] =
                        dp[i - 1][j]; // the ith num can't be used, use nums[0:i-1) to make up j
                } else {
                    // case1: the ith num is not used, use nums[0:i-1) to make up j
                    // case2: the ith num is used, use nums[0:i-1) to make up the remaining amount
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][diff];
                }
            }
        }
        return dp[n][target];
    }
};
