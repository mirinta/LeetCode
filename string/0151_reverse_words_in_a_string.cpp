#include <string>
#include <vector>

/**
 * Given an input string "s", reverse the order of the words.
 *
 * A word is defined as a sequence of non-space characters. The words in "s" will be separated by at
 * least one space.
 *
 * Return a string of the words in reverse order concatenated by a single space.
 *
 * Note that "s" may contain leading or trailing space or multiple spaces between two words. The
 * returned string should only have a single space separating the words. Do not include any extra
 * spaces.
 *
 * Example 1:
 * Input: "the sky is blue"
 * Output: "blue is sky the"
 *
 * Example 2:
 * Input: "  hello world  "
 * Output: "  world hello  "
 */

class Solution
{
public:
    std::string reverseWords(std::string s)
    {
        if (s.empty())
            return {};

        const int n = s.size();
        std::vector<std::string> words;
        int left = 0;
        int right = 0;
        while (left < n) {
            while (left < n && s[left] == ' ') {
                left++;
            }
            right = left;
            while (right < n && s[right] != ' ') {
                right++;
            }
            if (right - left > 0) {
                words.push_back(s.substr(left, right - left));
            }
            left = right;
        }
        std::reverse(words.begin(), words.end());
        std::string result;
        for (int i = 0; i < words.size(); ++i) {
            result.append(words[i]);
            if (i != words.size() - 1) {
                result.push_back(' ');
            }
        }
        return result;
    }
};