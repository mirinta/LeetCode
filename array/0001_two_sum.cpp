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
 *
 * ! 2 <= nums.length <= 10^4
 * ! -10^9 <= nums[i] <= 10^9
 * ! -10^9 <= target <= 10^9
 * ! Only one valid answer exists.
 */

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target)
    {
        std::unordered_map<int, int> map; // value to index
        // there's exactly one solution, it implies that all values are unique
        for (int i = 0; i < nums.size(); ++i) {
            const int diff = target - nums[i];
            if (!map.count(diff)) {
                map[nums[i]] = i;
            } else {
                return {map[diff], i};
            }
        }
        return {};
    }
};
