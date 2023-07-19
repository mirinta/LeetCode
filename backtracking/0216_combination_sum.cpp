#include <vector>

/**
 * Find all valid combinations of "k" numbers that sum up to "n" such that the following conditions
 * are true:
 *
 * - Only numbers 1 through 9 are used.
 *
 * - Each number is used at most once.
 *
 * Return a list of all possible valid combinations. The list must not contain the same combination
 * twice, and the combinations may be returned in any order.
 *
 * ! 2 <= k <= 9
 * ! 1 <= n <= 60
 */

class Solution
{
public:
    std::vector<std::vector<int>> combinationSum3(int k, int n)
    {
        if (!isSovable(k, n))
            return {};

        std::vector<std::vector<int>> result;
        std::vector<int> combination;
        backtrack(result, combination, 1, k, n);
        return result;
    }

private:
    bool isSovable(int k, int n)
    {
        if (k > 9 || k < 1)
            return false;

        const int max = (9 + 9 - k + 1) * k / 2;
        return max >= n;
    }

    void backtrack(std::vector<std::vector<int>>& result, std::vector<int>& combination,
                   int current, int limit, int target)
    {
        if (combination.size() == limit && target == 0) {
            result.push_back(combination);
            return;
        }
        for (int i = current; i <= 9; ++i) {
            combination.push_back(i);
            backtrack(result, combination, i + 1, limit, target - i);
            combination.pop_back();
        }
    }
};