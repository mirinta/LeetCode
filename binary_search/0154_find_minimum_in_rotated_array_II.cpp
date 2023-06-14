#include <vector>

/**
 * Suppose an array of length "n" sorted in ascending order is rotated between 1 and n times. For
 * example, the array nums = [0,1,4,4,5,6,7] might become:
 *
 * - [4,5,6,7,0,1,4] if it was rotated 4 times.
 *
 * - [0,1,4,4,5,6,7] if it was rotated 7 times.
 *
 * Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array
 * [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
 *
 * Given the sorted rotated array nums that may contain duplicates, return the minimum element of
 * this array.
 *
 * You must decrease the overall operation steps as much as possible.
 *
 * ! n == nums.length
 * ! 1 <= n <= 5000
 * ! -5000 <= nums[i] <= 5000
 * ! nums is sorted and rotated between 1 and n times.
 */

class Solution
{
public:
    int findMin(const std::vector<int>& nums)
    {
        const auto n = nums.size();
        if (n <= 1)
            return n == 1 ? nums[0] : 0;

        // NOTE: the array may contain duplicates
        // no way to early return
        // | 1 1 | 0 1 |
        int left = 0;
        int right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) {
                // nums[left:mid] are in the right part, skip them
                left = mid + 1;
            } else if (nums[mid] < nums[right]) {
                // nums[mid] is in the left part, shrink its size
                right = mid;
            } else {
                // nums[mid] == nums[right],
                // no way to determine which part contains nums[mid],
                // we can simply skip nums[right]
                right -= 1;
            }
        }
        return nums[left];
    }
};