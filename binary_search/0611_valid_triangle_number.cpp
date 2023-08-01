#include <algorithm>
#include <vector>

/**
 * Given an integer array nums, return the number of triplets chosen from the array that can make
 * triangles if we take them as side lengths of a triangle.
 *
 * ! 1 <= nums.length <= 1000
 * ! 0 <= nums[i] <= 1000
 */

class Solution
{
public:
    int triangleNumber(std::vector<int>& nums)
    {
        if (nums.size() < 3)
            return 0;

        // a valid triangle: nums[i] + nums[j] > nums[k]
        // 2 3 4 5 6
        // i j k
        std::sort(nums.begin(), nums.end());
        int result = 0;
        for (int i = 0; i < nums.size() - 2; ++i) {
            if (nums[i] == 0)
                continue;

            int k = i + 2;
            for (int j = i + 1; j < nums.size() - 1; ++j) {
                while (k < nums.size() && nums[i] + nums[j] > nums[k]) {
                    k++;
                }
                result += k - 1 - j;
            }
        }
        return result;
    }
};