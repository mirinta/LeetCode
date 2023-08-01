#include <vector>

/**
 * You are given a sorted array consisting of only integers where every element appears exactly
 * twice, except for one element which appears exactly once.
 *
 * Return the single element that appears only once.
 *
 * Your solution must run in O(log n) time and O(1) space.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^5
 */

class Solution
{
public:
    int singleNonDuplicate(std::vector<int>& nums)
    {
        // nums.size is odd
        // L ... M-2 M-1 M M+1 M+2... R
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            const bool isLeftPartEvenSize = mid % 2 == 0;
            if (nums[mid] == nums[mid - 1]) {
                if (isLeftPartEvenSize) {
                    hi = mid - 2;
                } else {
                    lo = mid + 1;
                }
            } else if (nums[mid] == nums[mid + 1]) {
                if (isLeftPartEvenSize) {
                    lo = mid + 2;
                } else {
                    hi = mid - 1;
                }
            } else {
                return nums[mid];
            }
        }
        return nums[lo];
    }

private:
    // time O(n), space O(1)
    int approach1(std::vector<int>& nums)
    {
        int result = 0;
        for (const auto& val : nums) {
            result ^= val;
        }
        return result;
    }
};