#include <stack>
#include <string>
#include <vector>

/**
 * You are given an array of strings "tokens" that represents an arithmetic expression in a Reverse
 * Polish Notation.
 *
 * Evaluate the expression. Return an integer that represents the value of the expression.
 *
 * Note that:
 *
 * - The valid operators are '+', '-', '*', and '/'.
 *
 * - Each operand may be an integer or another expression.
 *
 * - The division between two integers always truncates toward zero.
 *
 * - There will not be any division by zero.
 *
 * - The input represents a valid arithmetic expression in a reverse polish notation.
 *
 * - The answer and all the intermediate calculations can be represented in a 32-bit integer.
 *
 * ! tokens[i] is either an operator or an integer.
 */

class Solution
{
public:
    int evalRPN(const std::vector<std::string>& tokens)
    {
        std::stack<int> stack;
        const std::string k_addition = "+";
        const std::string k_subtraction = "-";
        const std::string k_multiplication = "*";
        const std::string k_division = "/";
        for (const auto& s : tokens) {
            if (s == k_addition) {
                const auto pair = pop2Nums(stack);
                stack.push(pair.first + pair.second);
            } else if (s == k_subtraction) {
                const auto pair = pop2Nums(stack);
                stack.push(pair.second - pair.first);
            } else if (s == k_multiplication) {
                const auto pair = pop2Nums(stack);
                stack.push(pair.first * pair.second);
            } else if (s == k_division) {
                const auto pair = pop2Nums(stack);
                stack.push(pair.second / pair.first);
            } else {
                stack.push(std::stoi(s));
            }
        }
        return stack.top();
    }

private:
    std::pair<int, int> pop2Nums(std::stack<int>& stack)
    {
        const auto first = stack.top();
        stack.pop();
        const auto second = stack.top();
        stack.pop();
        return {first, second};
    }
};