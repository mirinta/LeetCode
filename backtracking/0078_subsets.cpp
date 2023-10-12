#include <vector>

/**
 * Given an integer array "nums" of unique elements, return all possible subsets (the power set).
 *
 * A subset of an integer is a selection of elements (possibly none) of the array
 *
 * The solution set, must not contain duplicate subsets. Return the solution in any order.
 *
 * ! 1 <= nums.length <= 10
 * ! -10 <= nums[i] <= 10
 * ! All the numbers of nums are unique.
 */

class Solution
{
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums)
    {
        std::vector<int> subset;
        backtrack(subset, 0, nums);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void backtrack(std::vector<int>& subset, int i, const std::vector<int>& nums)
    {
        result.push_back(subset);
        for (int j = i; j < nums.size(); ++j) {
            subset.push_back(nums[j]);
            backtrack(subset, j + 1, nums);
            subset.pop_back();
        }
    }
};
