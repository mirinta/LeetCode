#include <vector>

/**
 * Given an integer array "nums", move all 0's to then end of it while maintaining the relative
 * order of the non-zero elements.
 *
 * Note that you must do this in-place without making a copy of the array.
 *
 * ! 1 <= nums.length <= 10^4
 * ! -2^31 <= nums[i] <= 2^31 - 1
 */

class Solution
{
public:
    void moveZeroes(std::vector<int>& nums)
    {
        int nonZero = 0;
        for (const auto& val : nums) {
            if (val != 0) {
                nums[nonZero++] = val;
            }
        }
        while (nonZero < nums.size()) {
            nums[nonZero++] = 0;
        }
    }
};
