#include <vector>

/**
 * Given an array of distinct integers "nums" and a target integer "target", return the number of
 * possible combinations that add up to "target".
 *
 * The test case are generated so that the answer can fit in a 32-bit integer.
 *
 * Example:
 * Input: nums = [1, 2, 3], target = 4
 * Output: 7
 * Explanation:
 * The possible combination ways are:
 * (1, 1, 1, 1)
 * (1, 1, 2)
 * (1, 2, 1)
 * (1, 3)
 * (2, 1, 1)
 * (2, 2)
 * (3, 1)
 * Note that different sequences are counted as different combinations.
 *
 * ! 1 <= nums.length <= 200
 * ! 1 <= nums[i] <= 1000
 * ! All the elements of nums are unique.
 * ! 1 <= target <= 1000
 */

class Solution
{
public:
    int combinationSum4(const std::vector<int>& nums, int target)
    {
        // nums contains positive integers
        if (nums.empty() || target < 1)
            return 0;

        // dp[i] = number of possible combinations to adding up to "i"
        // - choices: all values of nums
        // - nums[j] can be picked if i-nums[j] >= 0
        // - if nums[j] is valid, the remaining target is i-nums[j], and there are dp[i-nums[j]]
        // ways to do that base case: dp[0]=1
        std::vector<unsigned> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; ++i) {
            for (const auto& val : nums) {
                if (i - val < 0)
                    continue;

                dp[i] += dp[i - val];
            }
        }
        return dp[target];
    }
};