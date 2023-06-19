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
        // at least one element, and all elements are unique
        // [LEFT...][...RIGHT]
        // if LEFT < RIGHT, nums is not rotated (i.e., rotation times % n = 0)
        int left = 0;
        int right = nums.size() - 1;
        if (nums[left] < nums[right])
            return nums[left];

        // the minimum is at the beginning of the right part,
        // so we need to find the right part,
        // and shrink its size until there's only one element in it
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[right]) {
                // mid is in the right part
                // [LEFT...][TARGET...M...RIGHT]
                //           | wanted |
                right = mid; // not mid-1, because we don't know whether nums[mid] is the target
            } else {
                // mid is in the left part, nums[mid] is definitely not the target
                // we don't need the left part, so skip nums[left:mid]
                // [LEFT...M M+1...][TARGET...RIGHT]
                //           |       wanted       |
                left = mid + 1;
            }
        }
        return nums[left];
    }
};
