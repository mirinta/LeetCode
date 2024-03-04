#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You are given an array nums consisting of positive integers.
 *
 * We call a subarray of an array complete if the following condition is satisfied:
 *
 * The number of distinct elements in the subarray is equal to the number of distinct elements in
 * the whole array. Return the number of complete subarrays.
 *
 * A subarray is a contiguous non-empty part of an array.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 2000
 */

class Solution
{
public:
    int countCompleteSubarrays(std::vector<int>& nums)
    {
        const int n = nums.size();
        const int distinct = std::unordered_set<int>(nums.begin(), nums.end()).size();
        std::unordered_map<int, int> map;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            map[nums[right]]++;
            while (map.size() == distinct) {
                if (--map[nums[left]] == 0) {
                    map.erase(nums[left]);
                }
                left++;
            }
            result += left; // nums[x:right] is valid where x can be 0~left-1
        }
        return result;
    }
};