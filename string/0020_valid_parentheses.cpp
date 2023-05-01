#include <stack>
#include <string>

/**
 * Given a string "s" containing just the characters '(', ')', '{', '}', '[' and ']', determine if
 * the input string is valid.
 *
 * An input string is valid if:
 *
 * - Open brackets must be closed by the same type of brackets.
 *
 * - Open brackets must be closed in the correct order.
 *
 * - Every close brackets has a corresponding open bracket of the same type.
 */

class Solution
{
public:
    bool isValid(const std::string& s)
    {
        if (s.empty())
            return false;

        constexpr char k_parenthesis_open = '(';
        constexpr char k_parenthesis_close = ')';
        constexpr char k_bracket_open = '[';
        constexpr char k_bracket_close = ']';
        constexpr char k_brace_open = '{';
        constexpr char k_brace_close = '}';
        std::stack<char> stack;
        for (const auto& c : s) {
            if (c == k_parenthesis_open) {
                stack.push(k_parenthesis_close);
            } else if (c == k_bracket_open) {
                stack.push(k_bracket_close);
            } else if (c == k_brace_open) {
                stack.push(k_brace_close);
            } else if (!stack.empty() && stack.top() == c) {
                stack.pop();
            } else {
                return false;
            }
        }
        return stack.empty();
    }
};