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
    std::vector<std::vector<int>> subsets(const std::vector<int>& nums)
    {
        std::vector<int> path;
        // backtrack1(path, 0, nums);
        backtrack2(path, 0, nums);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    // approach1:
    // enumerate a new value and add it to the path,
    // value = nums[j], j is in the range [i,n)
    void backtrack1(std::vector<int>& path, int i, const std::vector<int>& nums)
    {
        result.push_back(path);
        if (i == nums.size())
            return;

        for (int j = i; j < nums.size(); ++j) {
            path.push_back(nums[j]);
            backtrack1(path, j + 1, nums);
            path.pop_back();
        }
    }

    // approach2: choose/ignore nums[i]
    void backtrack2(std::vector<int>& path, int i, const std::vector<int>& nums)
    {
        if (i == nums.size()) {
            result.push_back(path);
            return;
        }
        path.push_back(nums[i]);
        backtrack2(path, i + 1, nums);
        path.pop_back();
        backtrack2(path, i + 1, nums);
    }
};
