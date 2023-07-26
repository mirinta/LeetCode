#include <vector>

/**
 * Given two integers "n" and "k", return all possible combinations of "k" numbers chosen from the
 * range "[1, n]";
 *
 * You may return the answer in any order.
 *
 * Example:
 * Input: n = 4, k = 2
 * Output: [[1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]]
 * Explanation: There are 4 choose 2 = 6 total combinations.
 * Note that combinations are unordered, i.e., [1, 2] and [2, 1] are considered to be the same
 * combination.
 *
 * ! 1 <= n <= 20
 * ! 1 <= k <= n
 */

class Solution
{
public:
    std::vector<std::vector<int>> combine(int n, int k)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> combination;
        backtrack(result, combination, 1, n, k);
        return result;
    }

private:
    void backtrack(std::vector<std::vector<int>>& result, std::vector<int>& combination, int start,
                   int n, int k)
    {
        if (combination.size() == k) {
            result.push_back(combination);
            return;
        }
        for (int i = start; i <= n; ++i) {
            combination.push_back(i);
            backtrack(result, combination, i + 1, n, k);
            combination.pop_back();
        }
    }
};