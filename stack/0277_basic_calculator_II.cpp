#include <stack>
#include <string>

/**
 * Given a string s which represents an expression, evaluate this expression and return its value.
 *
 * The integer division should truncate toward zero.
 *
 * You may assume that the given expression is always valid. All intermediate results will be in the
 * range of [-2^31, 2^31 - 1].
 *
 * Note: You are not allowed to use any built-in function which evaluates strings as mathematical
 * expressions, such as eval().
 *
 * ! 1 <= s.length <= 3 * 10^5
 * ! s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
 * ! s represents a valid expression.
 * ! All the integers in the expression are non-negative integers in the range [0, 2^31 - 1].
 * ! The answer is guaranteed to fit in a 32-bit integer.
 */

class Solution
{
public:
    int calculate(std::string s)
    {
        char prevOperator = '+'; // all values are non-negative
        s.push_back('+');        // "dummy" operator, just to make sure the last operator is handled
        int num = 0;
        std::stack<int> stack;
        for (const auto& c : s) {
            if (c == ' ')
                continue;

            if (std::isdigit(c)) {
                num = num * 10 + (c - '0');
                continue;
            }
            if (prevOperator == '+') {
                stack.push(num);
            } else if (prevOperator == '-') {
                stack.push(-num);
            } else if (prevOperator == '*') {
                const auto top = stack.top();
                stack.pop();
                stack.push(top * num);
            } else if (prevOperator == '/') {
                const auto top = stack.top();
                stack.pop();
                stack.push(top / num);
            }
            num = 0;
            prevOperator = c;
        }
        int result = 0;
        while (!stack.empty()) {
            result += stack.top();
            stack.pop();
        }
        return result;
    }
};
