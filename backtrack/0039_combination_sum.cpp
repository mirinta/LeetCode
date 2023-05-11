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
 * ! All elements of "candidates" are distinct.
 *
 * Example:
 * Input: candidates = [2, 3, 6, 7], target = 7
 * Output: [[2, 2, 3], [7]]
 */

class Solution
{
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target)
    {
        if (candidates.empty())
            return {};

        std::vector<int> combination;
        backtrack(combination, target, 0, candidates);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void backtrack(std::vector<int>& combination, int target, int start,
                   std::vector<int>& candidates)
    {
        if (target == 0) {
            result.push_back(combination);
            return;
        }
        for (int i = start; i < candidates.size(); ++i) {
            const auto diff = target - candidates[i];
            if (diff < 0)
                continue;

            combination.push_back(candidates[i]);
            // the next round still starts from i,
            // because the same number may be chosen for multiple times
            backtrack(combination, diff, i, candidates);
            combination.pop_back();
        }
    }
};