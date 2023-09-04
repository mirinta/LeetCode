#include <vector>

/**
 * You are given an integer array nums. You are initially positioned at the array's first index, and
 * each element in the array represents your maximum jump length at that position.
 *
 * Return true if you can reach the last index, or false otherwise.
 *
 * ! 1 <= nums.length <= 10^4
 * ! 0 <= nums[i] <= 10^5
 */

class Solution
{
public:
    bool canJump(std::vector<int>& nums)
    {
        int furthest = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (i > furthest)
                return false;

            furthest = std::max(furthest, i + nums[i]);
        }
        return furthest >= nums.size() - 1;
    }
};