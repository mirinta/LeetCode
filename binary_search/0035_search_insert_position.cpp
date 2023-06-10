#include <vector>

/**
 * Given a sorted array of distinct integers and a target value, return the index if the target is
 * found. If not, return the index where it would be if it were inserted in order.
 *
 * You must write an algorithm with O(logN) runtime complexity.
 *
 * ! "nums" contains distinct values stored in ascending order.
 */

class Solution
{
public:
    int searchInsert(const std::vector<int>& nums, int target)
    {
        if (nums.empty())
            return 0;

        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - right) / 2;
            if (nums[mid] == target)
                return mid;

            if (nums[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } // the loop is terminated when left = right + 1;
        return left;
    }
};