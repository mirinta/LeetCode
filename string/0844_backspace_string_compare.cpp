#include <stack>
#include <string>

/**
 * Given two strings s and t, return true if they are equal when both are typed into empty text
 * editors. '#' means a backspace character.
 *
 * Note that after backspacing an empty text, the text will continue empty.
 *
 * ! 1 <= s.length, t.length <= 200
 * ! s and t only contain lowercase letters and '#' characters.
 */

class Solution
{
public:
    bool backspaceCompare(const std::string& s, const std::string& t) { return approach2(s, t); }

private:
    // two-pointers, time O(N), space O(1)
    bool approach2(const std::string& s, const std::string& t)
    {
        int idxS = s.size() - 1;
        int idxT = t.size() - 1;
        int countS = 0;
        int countT = 0;
        while (true) {
            while (idxS >= 0 && (s[idxS] == '#' || countS > 0)) {
                if (s[idxS--] == '#') {
                    countS++;
                } else {
                    countS--;
                }
            }
            while (idxT >= 0 && (t[idxT] == '#' || countT > 0)) {
                if (t[idxT--] == '#') {
                    countT++;
                } else {
                    countT--;
                }
            }
            if (idxS < 0 && idxT < 0)
                break;

            if (idxS < 0 || idxT < 0)
                return false;

            if (s[idxS--] != t[idxT--])
                return false;
        }
        return true;
    }

    // two stacks, time O(N), space O(N)
    bool approach1(const std::string& s, const std::string& t)
    {
        auto stack1 = genStack(s);
        auto stack2 = genStack(t);
        if (stack1.size() != stack2.size())
            return false;

        while (!stack1.empty() && !stack2.empty()) {
            if (stack1.top() != stack2.top())
                return false;

            stack1.pop();
            stack2.pop();
        }
        return true;
    }

    std::stack<char> genStack(const std::string& s)
    {
        std::stack<char> stack;
        for (const auto& c : s) {
            if (c != '#') {
                stack.push(c);
            } else if (!stack.empty()) {
                stack.pop();
            }
        }
        return stack;
    }
};
