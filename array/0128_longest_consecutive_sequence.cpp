#include <algorithm>
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
    int longestConsecutive(std::vector<int>& nums) { return approach2(nums); }

private:
    // time O(N), space O(N)
    int approach2(const std::vector<int>& nums)
    {
        std::unordered_set<int> set(nums.begin(), nums.end());
        int result = 0;
        for (const auto& val : nums) {
            // if val-1 is found, it indicates that val is not the
            // beginning of a consecutive sequence
            if (set.count(val - 1))
                continue;

            int current = val;
            int count = 0;
            while (set.count(current)) {
                set.erase(current);
                current++;
                count++;
            }
            result = std::max(result, count);
        }
        return result;
    }

    // time O(NlogN), space O(N+std::sort)
    int approach1(const std::vector<int>& nums)
    {
        std::unordered_set<int> set(nums.begin(), nums.end());
        std::vector<int> unique;
        for (const auto& val : set) {
            unique.push_back(val);
        }
        std::sort(unique.begin(), unique.end());
        int result = 0;
        int i = 0;
        while (i < unique.size()) {
            int j = i + 1;
            while (j < unique.size() && unique[j] - unique[j - 1] == 1) {
                j++;
            }
            result = std::max(result, j - i);
            i = j;
        }
        return result;
    }
};
