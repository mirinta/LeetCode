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
        std::sort(candidates.begin(), candidates.end());
        std::vector<int> path;
        backtrack(path, 0, target, candidates);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void backtrack(std::vector<int>& path, int i, int target, const std::vector<int>& candidates)
    {
        if (target == 0) {
            result.push_back(path);
            return;
        }
        for (int j = i; j < candidates.size(); ++j) {
            if (j > i && candidates[j] == candidates[j - 1])
                continue;

            // candidates is sorted in non-decreasing order
            // if candidates[j] is too large, we can skip the remaining numbers
            if (target - candidates[j] < 0)
                break;

            path.push_back(candidates[j]);
            backtrack(path, j + 1, target - candidates[j], candidates);
            path.pop_back();
        }
    }
};
