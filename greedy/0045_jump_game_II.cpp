#include <vector>

/**
 * You are given a 0-indexed array of integers nums of length n. You are initially positioned at
 * nums[0].
 *
 * Each element nums[i] represents the maximum length of a forward jump from index i. In other
 * words, if you are at nums[i], you can jump to any nums[i + j] where:
 *
 * - 0 <= j <= nums[i] and
 *
 * - i + j < n
 *
 * Return the minimum number of jumps to reach nums[n - 1]. The test cases are generated such that
 * you can reach nums[n - 1].
 *
 * ! 1 <= nums.length <= 10^4
 * ! 0 <= nums[i] <= 1000
 * ! It's guaranteed that you can reach nums[n - 1].
 */

class Solution
{
public:
    int jump(std::vector<int>& nums) { return approach3(nums); }

private:
    // Greedy, time O(N), space O(1)
    int approach3(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int end = 0;      // where the current jump ends
        int furthest = 0; // the furthest reachable index of the next jump
        int result = 0;
        for (int i = 0; i < n - 1; ++i) {
            furthest = std::max(furthest, i + nums[i]);
            if (i == end) {
                result++;
                end = furthest;
            }
        }
        return result;
    }

    // Like BFS, time O(N), space O(1)
    int approach2(const std::vector<int>& nums)
    {
        // indices: 0 1 2 3 4
        //    nums: 2 3 1 1 4
        const int n = nums.size();
        int left = 0; // reachable range [left, right]
        int right = 0;
        int result = 0;
        while (right < n - 1) {
            int furthest = 0;
            for (int i = left; i <= right; ++i) {
                furthest = std::max(furthest, i + nums[i]);
            }
            left = right + 1;
            right = furthest;
            result++;
        }
        return result;
    }

    // DP, time O(N^2), space O(N)
    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i] = min steps of jumping from index 0 to index i
        std::vector<int> dp(n, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            if (i + nums[i] >= n - 1) {
                dp[n - 1] = std::min(dp[n - 1], 1 + dp[i]);
                break;
            }
            for (int j = 1; j <= nums[i]; ++j) {
                dp[i + j] = std::min(dp[i + j], 1 + dp[i]);
            }
        }
        return dp[n - 1];
    }
};