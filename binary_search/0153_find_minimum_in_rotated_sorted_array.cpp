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
    int findMin(std::vector<int>& nums)
    {
        // at least one element, and all elements are unique
        // [LEFT...][...RIGHT]
        // if nums[left] < nums[right],
        // it means the given array is not rotated or rotation times % n = 0
        // thus, nums[left] is the minimum element
        int left = 0;
        int right = nums.size() - 1;
        if (nums[left] < nums[right])
            return nums[left];

        // the minimum element is always in the right part
        // [LEFT...][MIN...RIGHT]
        // thus, we need to locate the right part,
        // and try to shrink its size until there's only one element
        while (left < right) {
            const int mid = left + (right - left) / 2;
            if (nums[mid] < nums[right]) {
                // mid is in the right part
                // [LEFT...][MIN...MID...RIGHT]
                right = mid; // NOTE, not mid-1, because we don't know whether nums[mid] is the
                             // minimum element
            } else {
                // mid is in the left part
                // [LEFT...MID...][MIN...RIGHT]
                // since we're only interested in the right part,
                // we skip all elements in the range [LEFT,MID]
                left = mid + 1;
            }
        } // the loop ends when left = right
        return nums[left];
    }
};
