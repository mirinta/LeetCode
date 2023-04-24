#include <vector>

/**
 * Given in integer array "nums" sorted in non-decreasing order, return an array of the squares of
 * each number sorted in non-decreasing order.
 */

class Solution
{
public:
    std::vector<int> sortedSquares(const std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        std::vector<int> result(nums.size(), 0);
        int left = 0;
        int right = nums.size() - 1;
        for (int i = nums.size() - 1; i >= 0; --i) {
            if (nums[left] < 0 && nums[left] + nums[right] < 0) {
                result[i] = nums[left] * nums[left];
                left++;
            } else {
                result[i] = nums[right] * nums[right];
                right--;
            }
        }
        return result;
    }
};