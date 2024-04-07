#include <vector>

/**
 * You are given an array of integers nums. Return the length of the longest subarray of nums which
 * is either strictly increasing or strictly decreasing.
 *
 * ! 1 <= nums.length <= 50
 * ! 1 <= nums[i] <= 50
 */

class Solution
{
public:
    int longestMonotonicSubarray(std::vector<int>& nums)
    {
        return std::max(helper(nums, true), helper(nums, false));
    }

private:
    int helper(const std::vector<int>& nums, bool isIncreasing)
    {
        const int n = nums.size();
        int i = 0;
        int result = 1;
        while (i < n - 1) {
            int j = i + 1;
            while (j < n && nums[j] != nums[j - 1] && nums[j] > nums[j - 1] == isIncreasing) {
                j++;
            }
            result = std::max(result, j - i);
            i = j;
        }
        return result;
    }
};