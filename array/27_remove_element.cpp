#include <vector>

/// Given an integer array "nums" and an integer "val", remove all occurrences of "val" in "nums"
/// in-place. The order of the elements may be changed. Then return the number of elements in "nums"
/// which are not equal to "val".
///
/// Consider the number of elements in "nums" which are not equal to "val" be "k", to get accepted,
/// you need to do the following things:
///
/// - Change the array "nums" such that the first "k" elements of "nums" contain the elements which
/// are not equal to "val". The remaining elements of nums are not important as well as the size of
/// nums.
///
/// - Return "k".

class Solution
{
public:
    void moveZeroes(std::vector<int>& nums)
    {
        const auto size = nums.size();
        if (size <= 1)
            return;

        // similar to leet code 27:
        // move all non-zero elements to the front of the array
        size_t nonZeroCount = 0;
        for (size_t i = 0; i < size; ++i) {
            if (nums[i] != 0) {
                nums[nonZeroCount++] = nums[i];
            }
        }
        // set all remaining elements to 0
        for (; nonZeroCount < size; ++nonZeroCount) {
            nums[nonZeroCount] = 0;
        }
    }
};
