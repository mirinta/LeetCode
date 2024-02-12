#include <unordered_map>
#include <vector>

/**
 * Given an integer array nums and an integer k, return true if nums has a good subarray or false
 * otherwise.
 *
 * A good subarray is a subarray where:
 *
 * - its length is at least two, and
 *
 * - the sum of the elements of the subarray is a multiple of k.
 *
 * Note that:
 *
 * - A subarray is a contiguous part of the array.
 *
 * - An integer x is a multiple of k if there exists an integer n such that x = n * k. 0 is always a
 * multiple of k.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^9
 * ! 0 <= sum(nums[i]) <= 2^31 - 1
 * ! 1 <= k <= 2^31 - 1
 */

class Solution
{
public:
    bool checkSubarraySum(std::vector<int>& nums, int k)
    {
        // let sum[i] = sum of nums[0:i]
        // given sum[i] % k = remainder,
        // if map[remainder] = j, it means sum[j] % k = sum[i] % k
        // then (sum[i] - sum[j]) % k = 0, the valid subarray is nums[j+1:i]
        // it must have at least elements, i.e., i-j >= 2
        // corner case:
        // sum[i] % k = 0, the valid subarray is nums[0:i], length = i+1
        // thus, we initialize map[0] = -1
        const int n = nums.size();
        std::unordered_map<int, int> map; // remainder to index
        map[0] = -1;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            const int remainder = sum % k;
            if (!map.count(remainder)) {
                map[remainder] = i;
                continue;
            }
            if (i - map[remainder] >= 2)
                return true;
        }
        return false;
    }
};