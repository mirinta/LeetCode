#include <algorithm>
#include <vector>

/**
 * Given an integer array nums, return the largest perimeter of a triangle with a non-zero area,
 * formed from three of these lengths. If it is impossible to form any triangle of a non-zero area,
 * return 0.
 */

class Solution
{
public:
    int largestPerimeter(std::vector<int>& nums)
    {
        if (nums.size() < 3)
            return 0;

        std::sort(nums.begin(), nums.end(), std::greater<int>());
        for (size_t i = 0; i <= nums.size() - 3; ++i) {
            if (nums[i] <= 0)
                break;

            if (nums[i + 1] + nums[i + 2] > nums[i])
                return nums[i + 1] + nums[i + 2] + nums[i];
        }
        return 0;
    }
};