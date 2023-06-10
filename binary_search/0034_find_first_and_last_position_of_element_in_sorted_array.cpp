#include <vector>

/**
 * Given an array of integers "nums" sorted in non-decreasing order, find the starting and ending
 * position of a given "target" value.
 *
 * If "target" is not found in the array, return [-1, -1].
 *
 * You must write an algorithm with O(logN) runtime complexity.
 */

class Solution
{
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target)
    {
        if (nums.empty())
            return {-1, -1};

        return {findFirst(nums, target), findLast(nums, target)};
        // return {findFirstV2(nums, target), findLastV2(nums, target)};
    }

private:
    int findFirst(const std::vector<int>& nums, int target)
    {
        if (nums.empty())
            return -1;

        int left = 0;
        int right = nums.size(); // elements in range [left, right)
        while (left < right) {   // the operator is not <=
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid; // decrease upper bound, search in [left, mid)
            } else {
                left = mid + 1;
            }
        } // the loop is terminated when left = right = mid
        if (left == nums.size() || nums[left] != target)
            return -1;

        return left;
    }

    int findFirstV2(const std::vector<int>& nums, int target)
    {
        if (nums.empty())
            return -1;

        int left = 0;
        int right = nums.size() - 1; // elements in range [left, right]
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } // the loop is terminated when left = right + 1 = mid
        if (left == nums.size() || nums[left] != target)
            return -1;

        return left;
    }

    int findLast(const std::vector<int>& nums, int target)
    {
        if (nums.empty())
            return -1;

        int left = 0;
        int right = nums.size(); // elements in range [left, right)
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target) {
                left = mid + 1; // increase lower bound, search in [mid + 1, right)
            } else {
                right = mid;
            }
        } // the loop is terminated when left = right = mid + 1, thus mid = left - 1
        if (left - 1 < 0 || nums[left - 1] != target)
            return -1;

        return left - 1;
    }

    int findLastV2(const std::vector<int>& nums, int target)
    {
        if (nums.empty())
            return -1;

        int left = 0;
        int right = nums.size() - 1; // elements in range [left, right]
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target) {
                left = mid + 1; // increase lower bound, search in [mid + 1, right]
            } else {
                right = mid - 1;
            }
        } // the loop is terminated when left = right + 1 = mid + 1, thus mid = left - 1
        if (left - 1 < 0 || nums[left - 1] != target)
            return -1;

        return left - 1;
    }
};