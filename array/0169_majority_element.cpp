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
    int majorityElement(std::vector<int>& nums)
    {
        int target = 0;
        int count = 0;
        for (const auto& val : nums) {
            if (count == 0) {
                target = val;
                count = 1;
            } else if (val == target) {
                count++;
            } else {
                count--;
            }
        }
        return target;
    }

private:
    int approach1(std::vector<int>& nums)
    {
        // find the n/2-th largest element
        // worst case O(n^2)
        int lo = 0;
        int hi = nums.size() - 1;
        const int rank = nums.size() / 2;
        while (lo <= hi) {
            const int pos = partition(lo, hi, nums);
            if (pos == rank) {
                return nums[pos];
            } else if (pos > rank) {
                hi = pos - 1;
            } else {
                lo = pos + 1;
            }
        }
        return -1;
    }

    int partition(int lo, int hi, std::vector<int>& nums)
    {
        const int pivot = nums[lo];
        int i = lo + 1;
        int j = hi;
        while (true) {
            while (i <= hi && nums[i] <= pivot) {
                i++;
            }
            while (j >= 0 && nums[j] > pivot) {
                j--;
            }
            if (i >= j)
                break;

            std::swap(nums[i], nums[j]);
        }
        std::swap(nums[lo], nums[j]);
        return j;
    }
};