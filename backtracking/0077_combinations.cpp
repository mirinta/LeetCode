#include <vector>

/**
 * Given two integers "n" and "k", return all possible combinations of "k" numbers chosen from the
 * range "[1, n]";
 *
 * You may return the answer in any order.
 *
 * ! 1 <= n <= 20
 * ! 1 <= k <= n
 */

class Solution
{
public:
    std::vector<std::vector<int>> combine(int n, int k)
    {
        std::vector<int> path;
        backtrack2(path, 1, n, k);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    // approach1:
    // enumerate the ith number of the final answer (i is 1-indexed)
    void backtrack1(std::vector<int>& path, int i, int n, int k)
    {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        for (int j = i; j <= n; ++j) {
            path.push_back(j);
            backtrack1(path, j + 1, n, k);
            path.pop_back();
        }
    }

    // approach2:
    // choose/ignore value i, i is in the range [1,n]
    void backtrack2(std::vector<int>& path, int i, int n, int k)
    {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        if (i > n)
            return;

        path.push_back(i);
        backtrack2(path, i + 1, n, k);
        path.pop_back();
        backtrack2(path, i + 1, n, k);
    }
};
