#include <vector>

/**
 * Given two arrays nums1 and nums2.
 *
 * Return the maximum dot product between non-empty subsequences of nums1 and nums2 with the same
 * length.
 *
 * A subsequence of a array is a new array which is formed from the original array by deleting some
 * (can be none) of the characters without disturbing the relative positions of the remaining
 * characters. (ie, [2,3,5] is a subsequence of [1,2,3,4,5] while [1,5,3] is not).
 *
 * ! 1 <= nums1.length, nums2.length <= 500
 * ! -1000 <= nums1[i], nums2[i] <= 1000
 */

class Solution
{
public:
    int maxDotProduct(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        return approach2(nums1, nums2);
    }

private:
    // DP with space optimization, time O(MN), space O(N)
    int approach2(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        std::vector<int> dp(1 + n, INT_MIN);
        std::vector<int> prev(1 + n, INT_MIN);
        for (int i = 1; i <= m; ++i) {
            prev.assign(dp.begin(), dp.end());
            dp[0] = INT_MIN;
            for (int j = 1; j <= n; ++j) {
                const int case1 = std::max(0, prev[j - 1]) + nums1[i - 1] * nums2[j - 1];
                const int case2 = std::max(prev[j], dp[j - 1]);
                dp[j] = std::max(case1, case2);
            }
        }
        return dp[n];
    }

    // DP, time O(MN), space O(MN)
    int approach1(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        // dp[i][j] = max product between non-empty subsequences of nums1[0:i) and nums2[0:j)
        // base cases
        // - dp[i][0] = INT_MIN
        // - dp[0][j] = INT_MIN
        std::vector<std::vector<int>> dp(1 + m, std::vector<int>(1 + n, INT_MIN));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // X X X X i
                // Y Y Y j
                // case1: both nums[i-1] and nums[j-1] are picked
                // #NOTE# we want non-empty subsequences, if the rest part < 0, we only keep
                // nums[i-1] and nums[j-1]
                const int case1 = std::max(0, dp[i - 1][j - 1]) + nums1[i - 1] * nums2[j - 1];
                // case2: only nums[i-1] is picked, or only nums[j-1] is picked
                const int case2 = std::max(dp[i - 1][j], dp[i][j - 1]);
                dp[i][j] = std::max(case1, case2);
            }
        }
        return dp[m][n];
    }
};
