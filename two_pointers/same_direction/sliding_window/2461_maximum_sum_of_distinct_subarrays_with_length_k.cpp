#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums and an integer k. Find the maximum subarray sum of all the
 * subarrays of nums that meet the following conditions:
 *
 * - The length of the subarray is k, and
 *
 * - All the elements of the subarray are distinct.
 *
 * Return the maximum subarray sum of all the subarrays that meet the conditions. If no subarray
 * meets the conditions, return 0.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= k <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 */

class Solution
{
public:
    long long maximumSubarraySum(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::unordered_map<int, int> map;
        long long result = 0; // all nums[i] > 0
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            map[nums[i]]++;
            if (i >= k) {
                sum -= nums[i - k];
                if (--map[nums[i - k]] == 0) {
                    map.erase(nums[i - k]);
                }
            }
            if (map.size() == k) {
                result = std::max(result, sum);
            }
        }
        return result;
    }
};