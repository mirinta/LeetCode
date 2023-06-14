#include <vector>

/**
 * Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For
 * example, the array nums = [0, 1, 2, 3, 4, 5, 6, 7] might become:
 *
 * - [4,5,6,7,0,1,2] if it was rotated 4 times.
 *
 * - [0,1,2,4,5,6,7] if it was rotated 7 times.
 *
 * Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array
 * [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
 *
 * Given the sorted rotated array nums of unique elements, return the minimum element of this array.
 *
 * You must write an algorithm that runs in O(log n) time.
 *
 * ! n == nums.length
 * ! 1 <= n <= 5000
 * ! -5000 <= nums[i] <= 5000
 * ! All the integers of nums are unique.
 * ! nums is sorted and rotated between 1 and n times.
 */

class Solution
{
public:
    int findMin(const std::vector<int>& nums)
    {
        const auto n = nums.size();
        if (n <= 1)
            return n == 1 ? nums[0] : -1;

        // NOTE: all elements are unique
        int left = 0;
        int right = n - 1;
        // the array is not rotated if nums[end] > nums[start]
        if (nums[right] > nums[left])
            return nums[left];
        // the rotated array can be split into two parts:
        // | 3 4 5 | 1 2 |
        // the minimum element is in the right part
        // therefore, we need to find the right part,
        // and shrink it until there's only one element in it
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) {
                // nums[left:mid] are in the left part, skip them
                left = mid + 1;
            } else {
                // nums[mid] is in the right part, shrink its size
                right = mid;
            }
        }
        // the loop is terminated when left = right
        return nums[left];
    }
};