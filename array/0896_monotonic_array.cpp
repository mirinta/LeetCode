#include <vector>

/**
 * An array is monotonic if it is either monotone increasing or monotone decreasing.
 *
 * An array "nums" is monotone increasing if for all i <= j, nums[i] <= nums[j]. An array "nums" is
 * monotone decreasing if for all i <= j, nums[i] >= nums[j].
 *
 * Given an integer array "nums", return true if the given array is monotonic, or false otherwise.
 */

class Solution
{
public:
    bool isMonotonic(std::vector<int>& nums)
    {
        if (nums.empty())
            return false;

        if (nums.size() == 1)
            return true;

        // approach 1:
        // sign = -1, 0, or 1
        // -1 for unknown, 1 for increasing, 0 for decreasing
        // int sign = -1;
        // for (size_t i = 1; i < nums.size(); ++i) {
        //     if (nums[i] == nums[i - 1])
        //         continue;

        //     if (sign == -1) {
        //         sign = nums[i] > nums[0];
        //     } else if ((nums[i] > nums[i - 1]) ^ sign)
        //         return false;
        // }
        // return true;
        // approach 2:
        return isIncreasing(nums) || isDecreasing(nums);
    }

private:
    bool isIncreasing(const std::vector<int>& nums)
    {
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] < nums[i - 1])
                return false;
        }
        return true;
    }

    bool isDecreasing(const std::vector<int>& nums)
    {
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[i - 1])
                return false;
        }
        return true;
    }
};