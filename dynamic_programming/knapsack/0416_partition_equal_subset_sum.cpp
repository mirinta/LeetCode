#include <vector>

/**
 * Given an integer array "nums", return true if you can partition the array into two subsets such
 * that the sum of the elements in both subsets is equal or false otherwise.
 */

class Solution
{
public:
    // if canPartition = true,
    // then the sum of each subset = total sum of nums / 2 = M
    // consider it as a 0/1 knapsack problem:
    // - we have a knapsack of capacity M
    // - nums[i] represents the capacity that the ith package occupies
    // - is it possible to fill the knapsack?
    bool canPartition(std::vector<int>& nums)
    {
        int sum = 0;
        for (const auto& val : nums) {
            sum += val;
        }
        if (sum % 2 != 0)
            return false;

        const auto m = sum / 2;
        const auto n = nums.size();
        // dp[i][j] = can/can't fill a knapsack of capacity j with packages[0:i)
        // base case:
        // - dp[0][0] = true
        // - dp[0][j] = false, package list is empty
        // - dp[i][0] = true, put nothing into the knapsack
        // std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1, false));
        // for (int i = 0; i <= n; ++i) {
        //     dp[i][0] = true;
        // }
        // for (int i = 1; i <= n; ++i) {
        //     for (int j = 1; j <= m; ++j) {
        //         const auto remaining = j - nums[i - 1];
        //         if (remaining < 0) {
        //             dp[i][j] = dp[i - 1][j];
        //         } else {
        //             dp[i][j] = dp[i - 1][j] || dp[i - 1][remaining];
        //         }
        //     }
        // }
        // return dp[n][m];
        // since dp[i][...] is only dependent on dp[i - 1][...],
        // we can replace the 2D matrix with a 1D array
        // - dp[j] = can/can't fill the knapsack of capacity j
        std::vector<bool> dp(m + 1, false);
        dp[0] = true;
        for (int i = 0; i < n; ++i) {
            for (int j = m; j >= 1; --j) {
                if (j - nums[i] >= 0) {
                    dp[j] = dp[j] || dp[j - nums[i]];
                }
            }
        }
        return dp[m];
    }
};