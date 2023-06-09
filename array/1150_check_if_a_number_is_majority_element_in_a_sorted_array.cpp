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
    bool isMajorityElement(const std::vector<int>& nums, int target)
    {
        if (nums.empty())
            return false;

        const auto n = nums.size();
        const auto i = firstIndexOf(target, nums);
        if (i < 0)
            return false;

        const auto j = i + n / 2;
        return j < n && nums[j] == target;
    }

private:
    int firstIndexOf(int target, const std::vector<int>& nums)
    {
        // binary search
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] >= target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } // the loop is terminated when lo = hi + 1
        return lo == nums.size() || nums[lo] != target ? -1 : lo;
    }
};