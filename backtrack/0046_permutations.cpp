#include <vector>

/**
 * Given an array "nums" of distinct integers, return all the possible permutations. You can return
 * the answer in any order.
 *
 * ! All the integers of "nums" are unique.
 */

class Solution
{
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        std::vector<bool> visited(nums.size(), false);
        std::vector<int> permutation;
        backtrack(permutation, visited, nums);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void backtrack(std::vector<int>& permutation, std::vector<bool>& visited,
                   const std::vector<int>& nums)
    {
        if (permutation.size() == nums.size()) {
            result.push_back(permutation);
            return;
        }
        for (size_t i = 0; i < nums.size(); ++i) {
            if (visited[i])
                continue;

            visited[i] = true;
            permutation.push_back(nums[i]);
            backtrack(permutation, visited, nums);
            permutation.pop_back();
            visited[i] = false;
        }
    }
};