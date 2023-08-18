#include <vector>

/**
 * Given an array "nums" of distinct integers, return all the possible permutations. You can return
 * the answer in any order.
 *
 * ! 1 <= nums.length <= 6
 * ! -10 <= nums[i] <= 10
 * ! All the integers of nums are unique.
 */

class Solution
{
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> permutation;
        std::vector<bool> visited(nums.size(), false);
        backtrack(result, visited, permutation, nums);
        return result;
    }

private:
    void backtrack(std::vector<std::vector<int>>& result, std::vector<bool>& visited,
                   std::vector<int>& permutation, const std::vector<int>& nums)
    {
        if (permutation.size() == nums.size()) {
            result.push_back(permutation);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (visited[i])
                continue;

            visited[i] = true;
            permutation.push_back(nums[i]);
            backtrack(result, visited, permutation, nums);
            permutation.pop_back();
            visited[i] = false;
        }
    }
};