#include <unordered_map>
#include <vector>

/**
 * There are two types of soup: type A and type B. Initially, we have n ml of each type of soup.
 * There are four kinds of operations:
 *
 * 1. Serve 100 ml of soup A and 0 ml of soup B,
 *
 * 2. Serve 75 ml of soup A and 25 ml of soup B,
 *
 * 3. Serve 50 ml of soup A and 50 ml of soup B, and
 *
 * 4. Serve 25 ml of soup A and 75 ml of soup B.
 *
 * When we serve some soup, we give it to someone, and we no longer have it. Each turn, we will
 * choose from the four operations with an equal probability 0.25. If the remaining volume of soup
 * is not enough to complete the operation, we will serve as much as possible. We stop once we no
 * longer have some quantity of both types of soup.
 *
 * Note that we do not have an operation where all 100 ml's of soup B are used first.
 *
 * Return the probability that soup A will be empty first, plus half the probability that A and B
 * become empty at the same time. Answers within 10-5 of the actual answer will be accepted.
 *
 * ! 0 <= n <= 10^9
 */

class Solution
{
public:
    double soupServings(int n)
    {
        if (n > 4300) // empirical number
            return 1;

        const int amount = std::ceil(n * 1.0 / 25);
        std::unordered_map<int, std::unordered_map<int, double>> memo;
        return dfs(memo, amount, amount);
    }

private:
    static constexpr double P = 0.25;

    double dfs(std::unordered_map<int, std::unordered_map<int, double>>& memo, int i, int j)
    {
        if (i <= 0 && j > 0)
            return 1;

        if (i <= 0 && j <= 0)
            return 0.5;

        if (i > 0 && j <= 0)
            return 0;

        if (memo.count(i) && memo[i].count(j))
            return memo[i][j];

        double result = 0;
        result += dfs(memo, i - 4, j) * P;
        result += dfs(memo, i - 3, j - 1) * P;
        result += dfs(memo, i - 2, j - 2) * P;
        result += dfs(memo, i - 1, j - 3) * P;
        return memo[i][j] = result;
    }
};
