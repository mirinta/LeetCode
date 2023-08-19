#include <algorithm>
#include <vector>

/**
 * Given a collection of candidate numbers "candidates" and a target number "target", find all
 * unique combinations in "candidates" where the candidate numbers sum to "target".
 *
 * Each number in "candidates" may only be used once in the combinations.
 *
 * Note: The solution set must not contain duplicate combinations.
 *
 * ! 1 <= candidates.length <= 100
 * ! 1 <= candidates[i] <= 50
 * ! 1 <= target <= 30
 */

class Solution
{
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target)
    {
        if (candidates.empty())
            return {};

        // arrange duplicates together
        std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int>> result;
        std::vector<int> combination;
        backtrack(result, combination, 0, target, candidates);
        return result;
    }

private:
    void backtrack(std::vector<std::vector<int>>& result, std::vector<int>& combination, int start,
                   int target, const std::vector<int>& candidates)
    {
        if (target == 0) {
            result.push_back(combination);
            return;
        }
        for (int i = start; i < candidates.size(); ++i) {
            const int diff = target - candidates[i];
            if (diff < 0)
                continue;

            if (i > start && candidates[i] == candidates[i - 1])
                continue;

            combination.push_back(candidates[i]);
            // next round starts from i+1, because each number can only be used once
            backtrack(result, combination, i + 1, diff, candidates);
            combination.pop_back();
        }
    }
};
