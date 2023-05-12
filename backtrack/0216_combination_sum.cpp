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
 */

class Solution
{
public:
    std::vector<std::vector<int>> combinationSum3(int k, int n)
    {
        if (!isSolvable(k, n))
            return {};

        std::vector<int> combination;
        backtrack(combination, 1, n, k);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    bool isSolvable(int k, int n)
    {
        // example: k = 2, n = 18
        // the maximum sum of two unique numbers in range [1, 9] is 17
        int maxSum = 0;
        for (int i = k, val = 9; i > 0; --i, --val) {
            maxSum += val;
        }
        return maxSum >= n;
    }

    void backtrack(std::vector<int>& combination, int start, int target, int dimension)
    {
        if (combination.size() == dimension && target == 0) {
            result.push_back(combination);
            return;
        }
        for (int i = start; i <= 9; ++i) {
            const auto diff = target - i;
            if (diff < 0)
                continue;

            combination.push_back(i);
            backtrack(combination, i + 1, target - i, dimension);
            combination.pop_back();
        }
    }
};