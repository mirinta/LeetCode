#include <unordered_set>
#include <vector>

/**
 * Given an unsorted array of integers nums, return the length of the longest consecutive elements
 * sequence.
 *
 * You must write an algorithm that runs in O(n) time.
 *
 * ! 0 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution
{
public:
    int longestConsecutive(std::vector<int>& nums)
    {
        std::unordered_set<int> set(nums.begin(), nums.end());
        int result = 0;
        for (const auto& val : nums) {
            if (set.count(val - 1))
                continue;

            int current = val;
            int count = 0;
            while (set.count(current)) {
                current++;
                count++;
            }
            result = std::max(result, count);
        }
        return result;
    }
};