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
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            const bool isLeftPartOddSize = mid % 2;
            if (nums[mid] == nums[mid - 1]) {
                if (isLeftPartOddSize) {
                    lo = mid + 1;
                } else {
                    hi = mid - 2;
                }
            } else if (nums[mid] == nums[mid + 1]) {
                if (isLeftPartOddSize) {
                    hi = mid - 1;
                } else {
                    lo = mid + 2;
                }
            } else {
                return nums[mid];
            }
        }
        return nums[lo];
    }
};