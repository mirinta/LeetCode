#include <vector>

/**
 * Given an integer array nums which is sorted in ascending order and all of its elements are unique
 * and given also an integer k, return the kth missing number starting from the leftmost number of
 * the array.
 *
 * ! 1 <= nums.length <= 5 * 10^4
 * ! 1 <= nums[i] <= 10^7
 * ! nums is sorted in ascending order, and all the elements are unique.
 * ! 1 <= k <= 10^8
 */

class Solution
{
public:
    int missingElement(std::vector<int>& nums, int k) { return approach2(nums, k); }

private:
    // binary search, time O(logn), space O(1)
    int approach2(std::vector<int>& nums, int k)
    {
        // k=3
        // index: 0 1 2 3
        // value: 4 7 9 10
        // - between 4 and 9, expected 9-4-1=4 numbers, but there's only 2-0-1=1 number
        // - there're 4-1=3 missing numbers
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            const int missing = nums[mid] - nums.front() - mid;
            if (missing < k) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        // here, nums[lo] = 9 and nums[hi] = 7, we want nums[hi]
        return nums[hi] + k - (nums[hi] - nums.front() - hi);
    }

    // time O(n), space O(1)
    int approach1(std::vector<int>& nums, int k)
    {
        // 4 7 9 10
        // - 4 and 7, missing two numbers: [5, 6]
        // - 7 and 9, missing 1 number: [8]
        // - 9 and 10, missing 0 number: []
        for (int i = 0; i < nums.size() - 1; ++i) {
            const int missing = nums[i + 1] - nums[i] - 1;
            if (missing >= k)
                return nums[i] + k;

            k -= missing;
        }
        return nums.back() + k;
    }
};