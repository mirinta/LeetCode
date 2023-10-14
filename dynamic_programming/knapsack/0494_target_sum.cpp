#include <numeric>
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
 */

class Solution
{
public:
    int findTargetSumWays(std::vector<int>& nums, int target)
    {
        // divide nums into two parts: A and B
        // add '+' for each number in A, and add '-' for each number in B
        // we want A - B = target, and we know that A + B = total
        // then, A = (total + target) / 2, and A >= 0 because nums[i] >= 0
        // our goal is to find the num of different ways to make up A
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total + target < 0 || (total + target) % 2 != 0)
            return 0;

        return approach2(nums, (total + target) / 2);
    }

private:
    // DP with space optimization, time O(NM), space O(M)
    int approach2(const std::vector<int>& nums, int amount)
    {
        const int n = nums.size();
        std::vector<int> dp(amount + 1, 0);
        std::vector<int> prev(amount + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            prev = dp;
            for (int j = 0; j <= amount; ++j) {
                if (j - nums[i - 1] < 0) {
                    dp[j] = prev[j];
                } else {
                    dp[j] = prev[j] + prev[j - nums[i - 1]];
                }
            }
        }
        return dp[amount];
    }

    // DP, time O(NM), space O(NM)
    int approach1(const std::vector<int>& nums, int amount)
    {
        // dp[i][j] = num of ways to make up amount j with nums[0:i)
        // dp[i][j] = case1 + case2
        // - nums[i-1] is used, case1 = dp[i-1][j-nums[i-1]]
        // - nums[i-1] is not used, case2 = dp[i-1][j]
        // base cases:
        // - dp[0][0] = 1
        // - dp[0][j>0] = 0, no numbers to choose, no way to make up a positive j
        const int n = nums.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(amount + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= amount; ++j) {
                if (j - nums[i - 1] < 0) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        return dp[n][amount];
    }
};