#include <unordered_set>
#include <vector>

/**
 * You are given an integer array banned and two integers n and maxSum. You are choosing some number
 * of integers following the below rules:
 *
 * - The chosen integers have to be in the range [1, n].
 *
 * - Each integer can be chosen at most once.
 *
 * - The chosen integers should not be in the array banned.
 *
 * - The sum of the chosen integers should not exceed maxSum.
 *
 * Return the maximum number of integers you can choose following the mentioned rules.
 *
 * ! 1 <= banned.length <= 10^4
 * ! 1 <= banned[i], n <= 10^4
 * ! 1 <= maxSum <= 10^9
 */

class Solution
{
public:
    int maxCount(std::vector<int>& banned, int n, int maxSum)
    {
        std::unordered_set<int> set(banned.begin(), banned.end());
        int result = 0;
        for (int i = 1, sum = 0; i <= n; ++i) {
            if (set.count(i))
                continue;

            sum += i;
            if (sum > maxSum)
                break;

            result++;
        }
        return result;
    }
};