#include <algorithm>
#include <vector>

/**
 * Given an integer array "nums" that may contain duplicates, return all possible subsets (the power
 * set).
 *
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 */

class Solution
{
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        std::sort(nums.begin(), nums.end()); // to arrange repeated values together
        std::vector<int> subset;
        backtrack(subset, nums, 0);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void backtrack(std::vector<int>& subset, const std::vector<int>& nums, int start)
    {
        result.push_back(subset);
        for (int i = start; i < nums.size(); ++i) {
            if (i > start && nums[i] == nums[i - 1])
                continue;

            subset.push_back(nums[i]);
            backtrack(subset, nums, i + 1);
            subset.pop_back();
        }
    }
};
