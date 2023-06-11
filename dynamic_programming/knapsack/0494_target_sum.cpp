#include <vector>

/**
 * You are given an integer array "nums" and an integer "target".
 *
 * You want to build an expression out of nums by adding one of the symbols '+' and '-' before each
 * integer in "nums" and then concatenate all the integers.
 *
 * - For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before '1' and concatenate
 * them to build the expression "+2-1".
 *
 * Return the number of different expressions that you can build, which evaluates to "target".
 *
 * ! 0 <= nums[i] <= 1000
 *
 * Example:
 * Input: nums = [1, 1, 1, 1, 1], target = 3
 * Output: 5
 * Explanation: There are 5 ways to assign symbols to make the sum of nums to be target 3.
 * -1 + 1 + 1 + 1 + 1 = 3
 * +1 - 1 + 1 + 1 + 1 = 3
 * +1 + 1 - 1 + 1 + 1 = 3
 * +1 + 1 + 1 - 1 + 1 = 3
 * +1 + 1 + 1 + 1 - 1 = 3
 */

class Solution
{
public:
    int findTargetSumWays(std::vector<int>& nums, int target)
    {
        // approach 2: DP, knapsack
        // since '+' and '-' are the only two options,
        // the expression can be written as: sum(A) - sum(B) = target
        // also, we know that total sum of nums = sum(A) + sum(B)
        // combine these two equations, we have sum(A) = (target + total sum of nums) / 2
        // the problem turns into a knapsack problem (similar to LC 416 and LC 518):
        // - capacity of the knapsack is sum(A)
        // - packages = nums
        int sum = 0;
        for (const auto& val : nums) {
            sum += val;
        }
        if (std::abs(target) > sum || (sum + target) % 2 != 0)
            return 0;

        // dp[i][j] = number of ways of filling a knapsack of capacity j with packages [0:i)
        // base cases:
        // - dp[0][j != 0] = 0, package list is empty, no way to fill knapsack with non-zero
        // capacity
        // - dp[0][0] = 1, the only way to fill a zero capacity knapsack with no package is: do
        // nothing note that dp[i != 0][0] is not guaranteed to be 1, because nums may has zero
        // value element thus, j should start from 0, not 1!
        const auto n = nums.size();
        const auto m = (sum + target) / 2;
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (j - nums[i - 1] < 0) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
                    // dp[i-1][j-nums[i-1]], not dp[i][j - nums[i - 1]],
                    // because the ith number (package) can be used only one time
                }
            }
        }
        return dp[n][m];
    }

private:
    // approach 1: recursion with memo
    // [ ] v0 [ ] v1 [ ] v2 [ ] v3 [ ] v4 = target
    //  0      1      2      3      4      <- indicies of brackets
    // brackets and values can use the same indicies
    // fill the ith bracket with '+' or '-':
    // - '+' makes the target -= v[i]
    // - '-' makes the target += v[i]
    // int result = 0;

    // int findTargetSumWays_v1(vector<int>& nums, int target) {
    //     std::unordered_map<std::string, int> memo;
    //     return dp(memo, 0, target, nums);
    // }

    // int dp(std::unordered_map<std::string, int>& memo, int i, int target, const std::vector<int>&
    // nums) {
    //     if (i == nums.size())
    //         return target == 0 ? 1 : 0;

    //     std::string key;
    //     key += std::to_string(i);
    //     key += ' ';
    //     key += std::to_string(target);
    //     if (memo.count(key))
    //         return memo[key];

    //     memo[key] = dp(memo, i + 1, target + nums[i], nums) + dp(memo, i + 1, target - nums[i],
    //     nums); return memo[key];
    // }
};