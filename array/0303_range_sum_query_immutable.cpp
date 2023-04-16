#include <vector>

/**
 * Given an integer array "nums", handle multiple queries of the following type:
 *
 * Calculate the sum of the elements of "nums" between indices "left" and "right" inclusive where
 * left <= right.
 *
 * Implement the "NumArray" class:
 *
 * - "NumArray(int[] nums)" initializes the object with the integer array "nums".
 *
 * - "int sumRange(int left, int right)" returns the sum of the elements of "nums" between indices
 * "left" and "right" inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
 *
 * !At most 10^4 calls will be made to "sumRange".
 */

class NumArray
{
public:
    NumArray(std::vector<int>& nums) : _preSums(nums.size() + 1, 0)
    {
        for (size_t i = 0; i < nums.size(); ++i) {
            _preSums[i + 1] = _preSums[i] + nums[i];
        }
    }

    int sumRange(int left, int right) { return _preSums[right + 1] - _preSums[left]; }

private:
    // [0, sumRange[0,0], sumRange[0,1], ..., sumRange[0, N-1]]
    std::vector<int> _preSums;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */