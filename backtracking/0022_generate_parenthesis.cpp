#include <string>
#include <vector>

/**
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed
 * parentheses.
 *
 * ! 1 <= n <= 8
 */

class Solution
{
public:
    std::vector<std::string> generateParenthesis(int n)
    {
        std::vector<std::string> result;
        std::string combination;
        backtrack(result, combination, n, n);
        return result;
    }

private:
    void backtrack(std::vector<std::string>& result, std::string& combination, int remainingLeft,
                   int remainingRight)
    {
        if (remainingLeft == 0 && remainingRight == 0) {
            result.push_back(combination);
            return;
        }
        if (remainingLeft < 0 || remainingRight < 0 || remainingLeft > remainingRight)
            return;

        combination.push_back('(');
        backtrack(result, combination, remainingLeft - 1, remainingRight);
        combination.pop_back();

        combination.push_back(')');
        backtrack(result, combination, remainingLeft, remainingRight - 1);
        combination.pop_back();
    }
};