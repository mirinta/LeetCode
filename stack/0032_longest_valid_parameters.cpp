#include <stack>
#include <string>

/**
 * Given a string containing just the characters '(' and ')', return the length of the longest valid
 * (well-formed) parentheses substring.
 *
 * ! 0 <= s.length <= 3 * 10^4
 * ! s[i] is '(', or ')'.
 */

class Solution
{
public:
    int longestValidParentheses(std::string s)
    {
        std::stack<int> stack;
        int result = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                stack.push(i);
                continue;
            }
            // ... j k i
            // if s[i] = ) and s[k] = (,
            // it means s[j+1, i] is a valid substring, length = i-j
            // if j doesn't exist, it means s[0:i] is a valid substring, length = i+1
            if (!stack.empty() && s[stack.top()] == '(') {
                stack.pop();
                result = std::max(result, i - (stack.empty() ? -1 : stack.top()));
            } else {
                stack.push(i);
            }
        }
        return result;
    }
};