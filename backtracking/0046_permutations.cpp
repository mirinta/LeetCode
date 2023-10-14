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
        std::vector<int> path;
        std::vector<bool> used(nums.size(), false);
        backtrack(path, used, nums);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void backtrack(std::vector<int>& path, std::vector<bool>& used, const std::vector<int>& nums)
    {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i])
                continue;

            used[i] = true;
            path.push_back(nums[i]);
            backtrack(path, used, nums);
            used[i] = false;
            path.pop_back();
        }
    }
};