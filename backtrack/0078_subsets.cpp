#include <vector>

/**
 * Given an integer array "nums" of unique elements, return all possible subsets (the power set).
 *
 * A subset of an integer is a selection of elements (possibly none) of the array
 *
 * The solution set, must not contain duplicate subsets. Return the solution in any order.
 *
 * ! All the numbers of "nums" are unique.
 *
 * Example:
 * Input: nums = [1, 2, 3]
 * Output: [[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]]
 *
 * Example:
 * Input: nums = [0]
 * Output: nums = [[], [0]]
 */

class Solution
{
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        std::vector<int> subset;
        backtrack(nums, 0, subset);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void backtrack(const std::vector<int>& nums, int start, std::vector<int>& subset)
    {
        result.push_back(subset);
        for (int i = start; i < nums.size(); ++i) {
            subset.push_back(nums[i]);
            backtrack(nums, i + 1, subset);
            subset.pop_back();
        }
    }
};
