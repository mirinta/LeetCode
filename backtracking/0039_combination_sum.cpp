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
        std::vector<int> path; // sum of path[i] = target
        backtrack(path, 0, target, candidates);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    // enumerate a new value nums[j] where j is in the range [i,n)
    void backtrack(std::vector<int>& path, int i, int target, const std::vector<int>& candidates)
    {
        if (target == 0) {
            result.push_back(path);
            return;
        }
        for (int j = i; j < candidates.size(); ++j) {
            if (target - candidates[j] < 0)
                continue;

            path.push_back(candidates[j]);
            // the same number can be chosen unlimited number of times
            // thus, the range of the next round is still [j,n)
            backtrack(path, j, target - candidates[j], candidates);
            path.pop_back();
        }
    }
};
