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
        std::string path;
        backtrack(path, 0, 0, n);
        return result;
    }

private:
    std::vector<std::string> result;

    // enumerate the ith character of a well-formed parentheses
    // only two choices: ( or )
    // num of left parenthesis >= num of right parenthesis
    void backtrack(std::string& path, int leftParenthesis, int rightParenthesis, int n)
    {
        if (leftParenthesis < rightParenthesis || leftParenthesis > n || rightParenthesis > n)
            return;

        if (leftParenthesis == n && rightParenthesis == n) {
            result.push_back(path);
        }
        path.push_back('(');
        backtrack(path, leftParenthesis + 1, rightParenthesis, n);
        path.pop_back();
        path.push_back(')');
        backtrack(path, leftParenthesis, rightParenthesis + 1, n);
        path.pop_back();
    }
};