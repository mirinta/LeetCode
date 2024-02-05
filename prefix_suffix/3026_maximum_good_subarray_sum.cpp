#include <unordered_map>
#include <vector>

/**
 * You are given an array nums of length n and a positive integer k.
 *
 * A subarray of nums is called good if the absolute difference between its first and last element
 * is exactly k, in other words, the subarray nums[i..j] is good if |nums[i] - nums[j]| == k.
 *
 * Return the maximum sum of a good subarray of nums. If there are no good subarrays, return 0.
 *
 * ! 2 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 * ! 1 <= k <= 10^9
 */

class Solution
{
public:
    long long maximumSubarraySum(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        // presum[i] = sum of nums[0:i-1]
        std::vector<long long> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        std::unordered_map<int, long long> map; // nums[i] to min presum[i]
        long long result = LLONG_MIN;
        // given nums[j], nums[i] = nums[j] + k or nums[j] - k
        // to maximize the sum of nums[i:j] = presum[j+1] - presum[i]
        // we want the min value of presum[i]
        for (int j = 0; j < n; ++j) {
            if (map.find(nums[j] + k) != map.end()) {
                result = std::max(result, presum[j + 1] - map[nums[j] + k]);
            }
            if (map.find(nums[j] - k) != map.end()) {
                result = std::max(result, presum[j + 1] - map[nums[j] - k]);
            }
            map[nums[j]] =
                map.find(nums[j]) == map.end() ? presum[j] : std::min(map[nums[j]], presum[j]);
        }
        return result == LLONG_MIN ? 0 : result;
    }
};