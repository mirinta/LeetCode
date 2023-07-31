#include <vector>

/**
 * You are given two 0-indexed integer arrays nums and multipliers of size n and m respectively,
 * where n >= m.
 *
 * You begin with a score of 0. You want to perform exactly m operations. On the ith operation
 * (0-indexed) you will:
 *
 * - Choose one integer x from either the start or the end of the array nums.
 *
 * - Add multipliers[i] * x to your score. Note that multipliers[0] corresponds to the first
 * operation, multipliers[1] to the second operation, and so on.
 *
 * - Remove x from nums.
 *
 * Return the maximum score after performing m operations.
 *
 * ! n == nums.length
 * ! m == multipliers.length
 * ! 1 <= m <= 300
 * ! m <= n <= 105
 * ! -1000 <= nums[i], multipliers[i] <= 1000
 */

class Solution
{
public:
    int maximumScore(std::vector<int>& nums, std::vector<int>& multipliers)
    {
        // dp[i][j] = max score if we pick i elements from the front,
        // and pick j elements from the back
        //  X X X X X X X ....... X X X X X X X
        //  |i elements |         |j elements |
        const int m = multipliers.size();
        const int n = nums.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(m + 1, INT_MIN / 2));
        dp[0][0] = 0;
        int result = INT_MIN;
        for (int t = 1; t <= m; ++t) {
            for (int i = 0; i <= t; ++i) {
                const int j = t - i;
                if (i >= 1) {
                    dp[i][j] = std::max(dp[i][j], dp[i - 1][j] + nums[i - 1] * multipliers[t - 1]);
                }
                if (j >= 1) {
                    dp[i][j] = std::max(dp[i][j], dp[i][j - 1] + nums[n - j] * multipliers[t - 1]);
                }
                if (t == m) {
                    result = std::max(result, dp[i][j]);
                }
            }
        }
        return result;
    }
};