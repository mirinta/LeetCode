#include <stack>
#include <string>

/**
 * Given a string s representing a valid expression, implement a basic calculator to evaluate it,
 * and return the result of the evaluation.
 *
 * Note: You are not allowed to use any built-in function which evaluates strings as mathematical
 * expressions, such as eval().
 *
 * ! 1 <= s.length <= 3 * 10^5
 * ! s consists of digits, '+', '-', '(', ')', and ' '.
 * ! s represents a valid expression.
 * ! '+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
 * ! '-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
 * ! There will be no two consecutive operators in the input.
 * ! Every number and running calculation will fit in a signed 32-bit integer.
 */

class Solution
{
public:
    int calculate(std::string s)
    {
        std::stack<int> stack;
        int num = 0;
        int sign = 1;
        int sum = 0;
        for (const auto& i : s) {
            if (std::isdigit(i)) {
                num = num * 10 + (i - '0');
            } else if (i == '-' || i == '+') {
                sum += sign * num;
                sign = i == '-' ? -1 : 1;
                num = 0;
            } else if (i == '(') {
                // SUM operator (...)
                stack.push(sum);  // store current sum
                stack.push(sign); // store sign before parenthesis
                sum = 0;
                num = 0;
                sign = 1;
            } else if (i == ')') {
                // PREV_SUM operator CURRENT_SUM
                sum += sign * num; // last operation in parenthesis
                sum *= stack.top();
                stack.pop();
                sum += stack.top();
                stack.pop();
                num = 0;
            }
        }
        return sum + sign * num;
    }
};
