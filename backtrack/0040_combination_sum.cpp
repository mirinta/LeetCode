#include <algorithm>
#include <vector>

/**
 * Given a collection of candidate numbers "candidates" and a target number "target", find all
 * unique combinations in "candidates" where the candidate numbers sum to "target".
 *
 * Each number in "candidates" may only be used once in the combinations.
 *
 * ! Note: The solution set must not contain duplicate combinations.
 */

class Solution
{
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target)
    {
        if (candidates.empty())
            return {};

        std::sort(candidates.begin(), candidates.end()); // arrange repeated values togeter
        std::vector<int> combination;
        backtrack(combination, candidates, 0, target);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void backtrack(std::vector<int>& combination, const std::vector<int>& nums, int start,
                   int target)
    {
        if (target == 0) {
            result.push_back(combination);
            return;
        }
        for (int i = start; i < nums.size(); ++i) {
            if (target - nums[i] < 0)
                continue;

            if (i > start && nums[i] == nums[i - 1])
                continue;

            combination.push_back(nums[i]);
            backtrack(combination, nums, i + 1, target - nums[i]);
            combination.pop_back();
        }
    }
};