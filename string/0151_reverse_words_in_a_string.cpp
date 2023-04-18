#include <string>
#include <sstream>

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
    // "  the sky  ":
    // - extract each word and reverse its characters, "eht" and "yks"
    // - concatenate the words with a single space, "eht yks"
    // - reverse the entire string, "sky the", done
    std::string reverseWords(const std::string& s)
    {
        if (s.empty())
            return {};

        std::istringstream stream{s};
        std::string result{};
        std::string word{};
        while (stream >> word) {
            reverseCharacters(word, 0, word.size());
            result += word + ' '; // an extra space is at the end
        }
        // without using std::istringstream:
        // const auto length = s.size();
        // int i = 0;
        // while (true) {
        //     while (i < length && s[i] == ' ') {
        //         i++;
        //     }
        //     if (i == length)
        //         break;
        //
        //     int start = i;
        //     while (i < length && s[i] != ' ') {
        //         i++;
        //     }
        //     auto word = s.substr(start, i - start);
        //     reverseCharacters(word, 0, word.size());
        //     result += word + ' '; // an extra space is at the end
        // }
        reverseCharacters(result, 0, result.size() - 1); // the extra space is at the end
        return result.substr(0, result.size() - 1);
    }

    // reverse characters in range [start, end)
    void reverseCharacters(std::string& s, int start, int end)
    {
        end--;
        while (start >= 0 && end < s.size() && start < end) {
            std::swap(s[start++], s[end--]);
        }
    }
};