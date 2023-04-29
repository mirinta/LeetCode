#include <unordered_map>
#include <vector>

/**
 * Given an array of integers "nums" and an integer "target", return indices of the two numbers such
 * that they add up to "target".
 *
 * You may assume that each input would have exactly one solution, and you may not use the same
 * element twice.
 *
 * You can return the answer in any order.
 */

class Solution
{
public:
    std::vector<int> twoSum(const std::vector<int>& nums, int target)
    {
        if (nums.empty() || nums.size() < 2)
            return {};

        std::unordered_map<int, int> map; // value to index
        for (int i = 0; i < nums.size(); ++i) {
            const auto diff = target - nums[i];
            if (map.count(diff))
                return {i, map[diff]};

            map[nums[i]] = i;
        }
        return {};
    }
};