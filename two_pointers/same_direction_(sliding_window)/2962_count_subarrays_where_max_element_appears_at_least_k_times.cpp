#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums and a positive integer k.
 *
 * Return the number of subarrays where the maximum element of nums appears at least k times in that
 * subarray.
 *
 * A subarray is a contiguous sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^6
 * ! 1 <= k <= 10^5
 */

class Solution
{
public:
    long long countSubarrays(std::vector<int>& nums, int k)
    {
        // 0 X X i-1 i X X X X X X j
        //           |<--k times-->|
        // valid subarrays:
        // - nums[i:j]
        // - nums[i-1:j]
        // - nums[i-2:j]
        // ...
        // - nums[0:j]
        // thus, num of valid subarrays = i + 1
        const int max = *std::max_element(nums.begin(), nums.end());
        const int n = nums.size();
        long long result = 0;
        for (int i = 0, j = 0, count = 0; j < n; ++j) {
            count += nums[j] == max ? 1 : 0;
            while (count == k) {
                count -= nums[i] == max ? 1 : 0;
                i++;
            }
            result += i;
        }
        return result;
    }
};