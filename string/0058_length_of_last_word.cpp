#include <string>

/**
 * Given a string "s" consisting of words and spaces, return the length of the last word in the
 * string.
 *
 * A word is a maximal substring consisting of non-space characters only.
 *
 * ! s consists of only English letters and spaces ' '.
 * ! There will be at least one word in "s".
 */

class Solution
{
public:
    int lengthOfLastWord(const std::string& s)
    {
        if (s.empty())
            return 0;

        int result = 0;
        for (int i = s.size() - 1; i >= 0; --i) {
            if (s[i] == ' ' && result == 0)
                continue;

            if (s[i] == ' ' && result > 0)
                break;

            result++;
        }
        return result;
    }
};