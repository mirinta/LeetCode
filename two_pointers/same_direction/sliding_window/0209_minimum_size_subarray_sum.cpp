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
    // sliding window, TC = O(N), SC = O(1)
    int approach2(int target, const std::vector<int>& nums)
    {
        int result = INT_MAX;
        for (int left = 0, right = 0, sum = 0; right < nums.size(); ++right) {
            sum += nums[right];
            while (sum >= target) {
                result = std::min(result, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }
        return result == INT_MAX ? 0 : result;
    }

    // prefix sum + binary search, TC = O(NlogN), SC = O(N)
    int approach1(int target, const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        int result = INT_MAX;
        for (int i = 0; i < n; ++i) {
            // sum[i:j] = presum[j+1] - presum[i] >= target
            auto iter = std::lower_bound(presum.begin(), presum.end(), target + presum[i]);
            if (iter != presum.end()) {
                const int jPlus1 = iter - presum.begin();
                result = std::min(result, jPlus1 - i);
            }
        }
        return result == INT_MAX ? 0 : result;
    }
};
