#include <unordered_map>
#include <vector>

/**
 * Given an integer array nums, return the largest integer that only occurs once. If no integer
 * occurs once, return -1.
 *
 * ! 1 <= nums.length <= 2000
 * ! 0 <= nums[i] <= 1000
 */

class Solution
{
public:
    int largestUniqueNumber(std::vector<int>& nums)
    {
        std::unordered_map<int, int> map; // val to frequency
        for (const auto& val : nums) {
            map[val]++;
        }
        int result = -1;
        for (const auto& [val, freq] : map) {
            if (freq == 1) {
                // nums[i] are positive integers
                result = std::max(result, val);
            }
        }
        return result;
    }
};
