#include <stack>
#include <string>

/**
 * Given a string expression representing arbitrarily nested ternary expressions, evaluate the
 * expression, and return the result of it.
 *
 * You can always assume that the given expression is valid and only contains digits, '?', ':', 'T',
 * and 'F' where 'T' is true and 'F' is false. All the numbers in the expression are one-digit
 * numbers (i.e., in the range [0, 9]).
 *
 * The conditional expressions group right-to-left (as usual in most languages), and the result of
 * the expression will always evaluate to either a digit, 'T' or 'F'.
 *
 * ! 5 <= expression.length <= 10^4
 * ! expression consists of digits, 'T', 'F', '?', and ':'.
 * ! It is guaranteed that expression is a valid ternary expression and that each number is a
 * ! one-digit number.
 */

class Solution
{
public:
    std::string parseTernary(std::string expression)
    {
        std::stack<char> stack;
        int i = expression.size() - 1;
        while (i > 0) {
            const auto& symbol = expression[i];
            if (symbol == '?') {
                const auto trueVal = stack.top();
                stack.pop();
                stack.pop(); // pop ':'
                const auto falseVal = stack.top();
                stack.pop();
                const auto condition = expression[i - 1];
                stack.push(condition == 'T' ? trueVal : falseVal);
                i--; // skip the "condition" character
            } else {
                stack.push(symbol);
            }
            i--;
        }
        std::string result;
        result.push_back(stack.top());
        return result;
    }
};