#include <vector>

/**
 * Given an integer array "nums", move all 0's to then end of it while maintaining the relative
 * order of the non-zero elements.
 *
 * Note that you must do this in-place without making a copy of the array.
 */

class Solution
{
public:
    void moveZeroes(std::vector<int>& nums)
    {
        // approach 1:
        // const auto size = nums.size();
        // if (size <= 1)
        //     return;

        // similar to leet code 27:
        // move all non-zero elements to the front of the array
        // size_t nonZeroCount = 0;
        // for (size_t i = 0; i < size; ++i) {
        //     if (nums[i] != 0) {
        //         nums[nonZeroCount++] = nums[i];
        //     }
        // }
        // set all remaining elements to 0
        // for (; nonZeroCount < size; ++nonZeroCount) {
        //     nums[nonZeroCount] = 0;
        // }
        // approach 2:
        if (nums.size() <= 1)
            return;

        size_t nonZero = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                std::swap(nums[i], nums[nonZero++]);
            }
        }
    }
};