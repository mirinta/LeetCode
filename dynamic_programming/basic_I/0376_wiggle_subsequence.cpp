#include <vector>

/**
 * @brief A wiggle sequence is a sequence where the differences between successive numbers strictly
 * alternate between positive and negative. The first difference (if one exists) may be either
 * positive or negative. A sequence with one element and a sequence with two non-equal elements are
 * trivially wiggle sequences.
 *
 * - For example, [1, 7, 4, 9, 2, 5] is a wiggle sequence because the differences (6, -3, 5, -7, 3)
 * alternate between positive and negative.
 *
 * - In contrast, [1, 4, 7, 2, 5] and [1, 7, 4, 5, 5] are not wiggle sequences. The first is not
 * because its first two differences are positive, and the second is not because its last difference
 * is zero.
 *
 * A subsequence is obtained by deleting some elements (possibly zero) from the original sequence,
 * laving the remaining elements in their original order.
 *
 * Given an integer array "nums", return the length of the longest wiggle subsequence of "nums".
 *
 * ! 1 <= nums.length <= 1000
 * ! 0 <= nums[i] <= 1000
 */

class Solution
{
public:
    int wiggleMaxLength(const std::vector<int>& nums)
    {
        // dp[i][j] = length of the longest wiggle subsequence that ends with nums[i]
        // - j is either 0 or 1
        // - dp[i][0] means the last difference of the subsequence is negative
        // - dp[i][1] means the last difference of the subsequence is positive
        const auto n = nums.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(2, 0));
        dp[0][0] = 1; // base case, only one character
        dp[0][1] = 1; // base case, only one character
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[i - 1]) {
                dp[i][0] = dp[i - 1][1] + 1;
                dp[i][1] = dp[i - 1][1];
            } else if (nums[i] > nums[i - 1]) {
                dp[i][1] = dp[i - 1][0] + 1;
                dp[i][0] = dp[i - 1][0];
            } else {
                dp[i][0] = dp[i - 1][0];
                dp[i][1] = dp[i - 1][1];
            }
        }
        return std::max(dp[n - 1][0], dp[n - 1][1]);
    }
};