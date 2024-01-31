#include <array>
#include <vector>

/**
 * A wiggle sequence is a sequence where the differences between successive numbers strictly
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
    int wiggleMaxLength(std::vector<int>& nums) { return approach3(nums); }

private:
    // DP2 with space optimization, TC = O(N), SC = O(1)
    int approach3(const std::vector<int>& nums)
    {
        // - pattern 0: Xn < Xn-1
        // - pattern 1: Xn > Xn-1
        const int n = nums.size();
        int pattern0 = 1;
        int pattern1 = 1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i - 1]) {
                pattern1 = 1 + pattern0;
            } else if (nums[i] < nums[i - 1]) {
                pattern0 = 1 + pattern1;
            }
        }
        return std::max(pattern0, pattern1);
    }

    // DP2, TC = O(N), SC = O(N)
    int approach2(const std::vector<int>& nums)
    {
        // - pattern 0: Xn < Xn-1
        // - pattern 1: Xn > Xn-1
        // dp[i][0] = length of the LWS of nums[0:i] in pattern1
        // dp[i][1] = length of the LWS of nums[0:i] in pattern2
        const int n = nums.size();
        std::vector<std::array<int, 2>> dp(n, {1, 1});
        int result = 1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i - 1]) {
                dp[i][1] = std::max(dp[i][1], 1 + dp[i - 1][0]);
                dp[i][0] = dp[i - 1][0];
            } else if (nums[i] < nums[i - 1]) {
                dp[i][0] = std::max(dp[i][0], 1 + dp[i - 1][1]);
                dp[i][1] = dp[i - 1][1];
            } else {
                dp[i] = dp[i - 1];
            }
            result = std::max({result, dp[i][0], dp[i][1]});
        }
        return result;
    }

    // DP1, TC = O(N^2), SC = O(N)
    int approach1(const std::vector<int>& nums)
    {
        // a valid wiggle sequence: {X1, ..., Xn-1, Xn}
        // - pattern 0: Xn < Xn-1
        // - pattern 1: Xn > Xn-1
        // dp[i][0] = length of the LWS of nums[0:i] in pattern 0 and it is ending at nums[i]
        // dp[i][1] = length of the LWS of nums[0:i] in pattern 1 and it is ending at nums[i]
        // single number is a valid wiggle subsequence with length = 1
        const int n = nums.size();
        std::vector<std::array<int, 2>> dp(n, {1, 1});
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] == nums[j])
                    continue;

                if (nums[i] > nums[j]) {
                    dp[i][1] = std::max(dp[i][1], 1 + dp[j][0]);
                } else {
                    dp[i][0] = std::max(dp[i][0], 1 + dp[j][1]);
                }
            }
            result = std::max({result, dp[i][0], dp[i][1]});
        }
        return result;
    }
};