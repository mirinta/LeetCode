#include <array>
#include <stack>
#include <string>

/**
 * Given a string s, remove duplicate letters so that every letter appears once and only once. You
 * must make sure your result is the smallest in lexicographical order among all possible results.
 *
 * ! 1 <= s.length <= 10^4
 * ! s consists of lowercase English letters.
 *
 * ! This question is the same as 1081.
 */

class Solution
{
public:
    std::string removeDuplicateLetters(std::string s)
    {
        constexpr int R = 26; // only lowercase English letters
        const int n = s.size();
        std::array<int, R> lastOccurrence{0};
        for (int i = 0; i < n; ++i) {
            lastOccurrence[s[i] - 'a'] = i;
        }
        std::array<bool, R> inStack{false};
        std::stack<char> stack;
        for (int i = 0; i < n; ++i) {
            if (inStack[s[i] - 'a'])
                continue;

            // maintain the stack as monotonically increasing as possible
            // if top_char > incoming_char and the top_char can be found later,
            // then pop top_char
            while (!stack.empty() && stack.top() > s[i] && lastOccurrence[stack.top() - 'a'] > i) {
                const auto top = stack.top();
                stack.pop();
                inStack[top - 'a'] = false;
            }
            stack.push(s[i]);
            inStack[s[i] - 'a'] = true;
        }
        std::string result(stack.size(), ' ');
        for (int i = result.size() - 1; i >= 0; --i) {
            result[i] = stack.top();
            stack.pop();
        }
        return result;
    }
};
