#include <vector>

/**
 * You are given an inclusive range [lower, upper] and a sorted unique integer array "nums", where
 * all elements are within the inclusive range.
 *
 * A number x is considered missing if x is in the range [lower, upper] and x is not in nums.
 *
 * Return the shortest sorted list of ranges that exactly covers all the missing numbers. That is,
 * no element of nums is included in any of the ranges, and each missing number is covered by one of
 * the ranges.
 *
 * ! -109 <= lower <= upper <= 109
 * ! 0 <= nums.length <= 100
 * ! lower <= nums[i] <= upper
 * ! All the values of nums are unique.
 */

class Solution
{
public:
    std::vector<std::vector<int>> findMissingRanges(const std::vector<int>& nums, int lower,
                                                    int upper)
    {
        if (lower > upper)
            return {};

        if (nums.empty())
            return {{lower, upper}};

        // lower = 0 [0, 1, 3, 50, 75] upper = 99
        // - check lower and 0, no missing numbers
        // - check 0 and 1, no missing numbers
        // - check 1 and 3, missing [2, 2]
        // - check 3 and 50, missing [4, 49]
        // - check 50 and 75, missing [51, 74]
        // - check 75 and upper, missing [76, 99]
        std::vector<std::vector<int>> result;
        if (lower < nums.front()) {
            result.push_back({lower, nums.front() - 1});
        }
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] - nums[i - 1] > 1) {
                result.push_back({nums[i - 1] + 1, nums[i] - 1});
            }
        }
        if (upper > nums.back()) {
            result.push_back({nums.back() + 1, upper});
        }
        return result;
    }
};