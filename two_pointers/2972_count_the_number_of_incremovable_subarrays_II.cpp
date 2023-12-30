#include <vector>

/**
 * You are given a 0-indexed array of positive integers nums.
 *
 * A subarray of nums is called incremovable if nums becomes strictly increasing on removing the
 * subarray. For example, the subarray [3, 4] is an incremovable subarray of [5, 3, 4, 6, 7] because
 * removing this subarray changes the array [5, 3, 4, 6, 7] to [5, 6, 7] which is strictly
 * increasing.
 *
 * Return the total number of incremovable subarrays of nums.
 *
 * Note that an empty array is considered strictly increasing.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution
{
public:
    long long incremovableSubarrayCount(std::vector<int>& nums)
    {
        // similar to LC 1574
        const int n = nums.size();
        int i = 0;
        while (i + 1 < n && nums[i] < nums[i + 1]) {
            i++;
        } // nums[0:i] is strictly increasing
        // if i == n - 1,
        // it means the original array is strictly increasing, we can remove any subarray of it
        if (i == n - 1)
            return (1 + n) * n / 2;

        // since nums[0:i] is strictly increasing
        // then we can remove i+2 subarrays based on nums[i+1:n-1]
        // - nums[i+1:n-1]
        // - nums[i:n-1]
        // - nums[i-1:n-1]
        // ...
        // - nums[0:n-1]
        long long result = i + 2;
        // next, we fix nums[j] as the last element of the modified array
        // then we need to find the largest i such that
        // nums[0:i] is strictly increasing and nums[j] < nums[j]
        // then we can remove i+2 subarrays:
        // - nums[i+1:j-1]
        // - nums[i:j-1]
        // - ...
        // - nums[0:j-1]
        for (int j = n - 1; j > 0; --j) {
            while (i >= 0 && nums[i] >= nums[j]) {
                i--;
            }
            if (j - 1 >= i + 1) {
                result += i + 2;
            }
            if (nums[j] <= nums[j - 1])
                break;
        }
        return result;
    }
};