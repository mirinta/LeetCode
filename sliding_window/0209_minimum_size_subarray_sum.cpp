#include <vector>

/**
 * Given an array of positive integers "nums" and a positive integer "target", return the minimal
 * length of a sub-array whose sum is greater than or equal to "target". If there is no such
 * sub-array, return 0 instead.
 *
 * ! 1 <= target <= 10^9
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^4
 */

class Solution
{
public:
    int minSubArrayLen(int target, std::vector<int>& nums) { return approach2(target, nums); }

private:
    // sliding window, time O(N), space O(1)
    int approach2(int target, const std::vector<int>& nums)
    {
        const int n = nums.size();
        int minLength = INT_MAX;
        int windowSum = 0;
        // ... LEFT ... RIGHT ...
        //     |<----sum--->|
        // all nums[i] are positive
        // - when moving "right", the window sum is monotonic increasing
        // - when moving "left", the window sum is monotonic decreasing
        // each element will be visited at most two times
        for (int left = 0, right = 0; right < n; ++right) {
            windowSum += nums[right];
            while (windowSum >= target) {
                minLength = std::min(minLength, right - left + 1);
                windowSum -= nums[left++];
            }
        }
        return minLength == INT_MAX ? 0 : minLength;
    }

    // prefix sum + binary search, time O(NlogN), space O(N)
    int approach1(int target, const std::vector<int>& nums)
    {
        const int n = nums.size();
        // let prefix[i] = nums[0]+...+nums[i]
        // if nums[i]+...+nums[j] >= target,
        // then prefix[j] - prefix[i-1] >= target
        // since nums[i] are positive integers,
        // then prefix[i] is monotonic increasing
        // thus, given prefix[i-1], we can apply binary search to find prefix[j]
        std::vector<int> prefixSum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
        }
        int result = INT_MAX;
        for (int i = 1; i <= n; ++i) {
            const int findingTarget = prefixSum[i - 1] + target;
            auto iter = std::lower_bound(prefixSum.begin(), prefixSum.end(), findingTarget);
            if (iter != prefixSum.end()) {
                const int j = std::distance(prefixSum.begin(), iter);
                result = std::min(result, j - i + 1);
            }
        }
        return result == INT_MAX ? 0 : result;
    }
};
