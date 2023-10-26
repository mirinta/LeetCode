#include <vector>

/**
 * Given an integer array "nums" sorted in non-decreasing order and an integer "target", return true
 * if target is a majority element, or false otherwise.
 *
 * A majority element in an array is an element that appears more than nums.length / 2 times in the
 * array.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i], target <= 10^9
 * ! nums is sorted in non-decreasing order.
 */

class Solution
{
public:
    bool isMajorityElement(std::vector<int>& nums, int target)
    {
        const int first = findFirst(target, nums);
        if (first < 0)
            return false;

        const int last = findLast(target, nums);
        if (last < 0)
            return false;

        return last - first + 1 > nums.size() / 2;
    }

private:
    int findFirst(int target, const std::vector<int>& nums)
    {
        const int n = nums.size();
        int lo = 0;
        int hi = n - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (nums[mid] >= target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        if (lo >= n || nums[lo] != target)
            return -1;

        return lo;
    }

    int findLast(int target, const std::vector<int>& nums)
    {
        const int n = nums.size();
        int lo = 0;
        int hi = n - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (nums[mid] <= target) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        if (hi < 0 || nums[hi] != target)
            return -1;

        return hi;
    }
};