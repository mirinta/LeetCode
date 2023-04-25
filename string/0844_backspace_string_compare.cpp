#include <stack>
#include <string>

/**
 * Given two strings "s" and "t", return "true" if they are equal when both are typed into empty
 * text editors. "#" means a backspace character.
 *
 * Note that after backspacing an empty text, the text will continue empty.
 */

class Solution
{
public:
    bool backspaceCompare(const std::string& s, const std::string& t)
    {
        // version 1: two stacks:
        std::stack<char> stackS;
        process(stackS, s);
        std::stack<char> stackT;
        process(stackT, t);
        if (stackS.size() != stackT.size())
            return false;

        for (; !stackS.empty() && !stackT.empty(); stackS.pop(), stackT.pop()) {
            if (stackS.top() != stackT.top())
                return false;
        }
        return true;
        // version 2: two pointers
        // const char backspace = '#';
        // int idxS = s.size() - 1;
        // int countS = 0;
        // int idxT = t.size() - 1;
        // int countT = 0;
        // while (true) {
        //     while (idxS >= 0 && (s[idxS] == backspace || countS > 0)) {
        //         s[idxS--] == backspace ? countS++ : countS--;
        //     }
        //     while (idxT >= 0 && (t[idxT] == backspace || countT > 0)) {
        //         t[idxT--] == backspace ? countT++ : countT--;
        //     }
        //     if (idxS < 0 || idxT < 0)
        //         break;

        //     if (s[idxS--] != t[idxT--])
        //         return false;
        // }
        // return idxS == idxT;
    }

private:
    void process(std::stack<char>& stack, const std::string& s)
    {
        const char backspace = '#';
        for (const auto& c : s) {
            if (c == backspace) {
                if (!stack.empty()) {
                    stack.pop();
                }
            } else {
                stack.push(c);
            }
        }
    }
};
