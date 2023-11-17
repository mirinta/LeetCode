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
        s.push_back('#'); // to make sure the last digit is handled
        std::stack<int> stack;
        char lastOperator = '+'; // all values are non-negative
        int num = 0;
        for (const auto& c : s) {
            if (c == ' ')
                continue;

            if (std::isdigit(c)) {
                num = num * 10 + (c - '0');
                continue;
            }
            switch (lastOperator) {
            case '+':
                stack.push(num);
                break;
            case '-':
                stack.push(-num);
                break;
            case '*':
            {
                const auto top = stack.top();
                stack.pop();
                stack.push(top * num);
                break;
            }
            case '/':
            {
                const auto top = stack.top();
                stack.pop();
                stack.push(top / num);
                break;
            }
            }
            num = 0;
            lastOperator = c;
        }
        int result = 0;
        while (!stack.empty()) {
            result += stack.top();
            stack.pop();
        }
        return result;
    }
};
