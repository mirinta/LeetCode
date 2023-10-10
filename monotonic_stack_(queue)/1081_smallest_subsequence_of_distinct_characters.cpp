#include <array>
#include <stack>
#include <string>

/**
 * Given a string s, return the lexicographically smallest subsequence of s that contains all the
 * distinct characters of s exactly once.
 *
 * ! 1 <= s.length <= 1000
 * ! s consists of lowercase English letters.
 *
 * ! This question is the same as 316.
 */

class Solution
{
public:
    std::string smallestSubsequence(std::string s)
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

            while (!stack.empty() && stack.top() > s[i] && lastOccurrence[stack.top() - 'a'] > i) {
                inStack[stack.top() - 'a'] = false;
                stack.pop();
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
