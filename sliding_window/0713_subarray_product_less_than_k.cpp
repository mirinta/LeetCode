#include <vector>

/**
 * Given an array of integers nums and an integer k, return the number of contiguous subarrays where
 * the product of all the elements in the subarray is strictly less than k.
 *
 * ! 1 <= nums.length <= 3 * 10^4
 * ! 1 <= nums[i] <= 1000
 * ! 0 <= k <= 10^6
 */

class Solution
{
public:
    int numSubarrayProductLessThanK(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        int result = 0;
        int product = 1;
        for (int left = 0, right = 0; right < n; ++right) {
            product *= nums[right];
            while (left <= right && product >= k) {
                product /= nums[left++];
            }
            // [left, right] is a valid window,
            // valid subarrays are:
            // [left, right], [left+1, right], ... , [right, right]
            result += right - left + 1;
        }
        return result;
    }
};