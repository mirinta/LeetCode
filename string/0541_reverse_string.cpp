#include <string>

/**
 * Given a string "s" and an integer "k", reverse the first "k" characters for every "2k" characters
 * counting from the start of the string.
 *
 * If there are fewer than "k" characters left, reverse all of them. If there are less than "2k" but
 * greater than or equal to "k" characters, then reverse the first "k" characters and leave the
 * other as original.
 */

class Solution
{
public:
    std::string reverseStr(const std::string& s, int k)
    {
        if (s.empty() || k < 1)
            return {};

        std::string result(s);
        const auto length = result.size();
        int i = 0;
        while (i + 2 * k <= length) {
            reverse(result, i, i + k - 1);
            i += 2 * k;
        }
        reverse(result, i, length - i >= k ? i + k - 1 : length - 1);
        return result;
    }

private:
    // characters in range [start, end]
    void reverse(std::string& s, int start, int end)
    {
        while (start < end && end < s.size()) {
            std::swap(s[start++], s[end--]);
        }
    }
};