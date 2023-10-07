#include <vector>

/**
 * Given an array nums of size n, return the majority element.
 *
 * The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the
 * majority element always exists in the array.
 *
 * ! n == nums.length
 * ! 1 <= n <= 5 * 10^4
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution
{
public:
    int majorityElement(std::vector<int>& nums) { return approach2(nums); }

private:
    // time O(N), space O(1)
    int approach2(const std::vector<int>& nums)
    {
        int count = 0;
        int majority = 0;
        for (const auto& val : nums) {
            if (count == 0) {
                majority = val;
                count = 1;
            } else if (val == majority) {
                count++;
            } else {
                count--;
            }
        }
        return majority;
    }

    // quick-select, find the n/2 th largest element
    int approach1(std::vector<int>& nums)
    {
        const int n = nums.size();
        const int rank = n / 2;
        int lo = 0;
        int hi = n - 1;
        while (lo < hi) {
            const auto [left, right] = threeWayPartition(nums, lo, hi);
            if (rank < left) {
                hi = left - 1;
            } else if (rank > right) {
                lo = right + 1;
            } else {
                return nums[rank];
            }
        }
        return nums[rank];
    }

    std::pair<int, int> threeWayPartition(std::vector<int>& nums, int lo, int hi)
    {
        // lo ... lt-1 lt ... gt gt+1 ... hi
        // |<------->| |<----->| |<------->|
        //    <pivot     =pivot     >pivot
        const int pivot = nums[lo];
        int i = lo;
        int lt = lo;
        int gt = hi;
        while (i <= gt) {
            if (nums[i] < pivot) {
                std::swap(nums[i++], nums[lt++]);
            } else if (nums[i] > pivot) {
                std::swap(nums[i], nums[gt--]);
            } else {
                i++;
            }
        }
        return {lt, gt};
    }
};
