#include <vector>

/**
 * Given an array of distinct integers "candidates" and a target integer "target", return a list of
 * all unique combinations of "candidates" where the chosen numbers sum to "target". You may return
 * the combinations in any order.
 *
 * The same number may be chosen from "candidates" an unlimited number of times. Two combinations
 * are unique if the frequency of at least one of the chosen numbers is different.
 *
 * The test cases are generated such that the number of unique combinations that sum up to "target"
 * is less than 150 combinations for the given input.
 *
 * ! 1 <= candidates.length <= 30
 * ! 2 <= candidates[i] <= 40
 * ! All elements of candidates are distinct.
 * ! 1 <= target <= 40
 */

class Solution
{
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target)
    {
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

            combination.push_back(candidates[i]);
            // next round still starts from candidates[i],
            // because the same number can be chosen multiple times
            backtrack(result, combination, i, diff, candidates);
            combination.pop_back();
        }
    }
};