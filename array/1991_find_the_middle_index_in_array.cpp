#include <vector>

/**
 * Given a 0-indexed integer array nums, find the leftmost middleIndex (i.e., the smallest amongst
 * all the possible ones).
 *
 * A middleIndex is an index where nums[0] + nums[1] + ... + nums[middleIndex-1] ==
 * nums[middleIndex+1] + nums[middleIndex+2] + ... + nums[nums.length-1].
 *
 * If middleIndex == 0, the left side sum is considered to be 0. Similarly, if middleIndex ==
 * nums.length - 1, the right side sum is considered to be 0.
 *
 * Return the leftmost middleIndex that satisfies the condition, or -1 if there is no such index.
 *
 * ! 1 <= nums.length <= 100
 * ! -1000 <= nums[i] <= 1000
 *
 * ! This question is the same as LC.724.
 */

class Solution
{
public:
    int findMiddleIndex(std::vector<int>& nums)
    {
        if (nums.size() <= 1)
            return nums.empty() ? -1 : 0;

        int totalSum = 0;
        for (const auto& val : nums) {
            totalSum += val;
        }
        int leftSum = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (leftSum == totalSum - nums[i] - leftSum)
                return i;

            leftSum += nums[i];
        }
        return -1;
    }
};
