#include <string>
#include <unordered_map>

/**
 * Given two strings "s" and "t", return "true" if "t" is an anagram of "s", and "false" otherwise.
 *
 * An anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
 * typically using all the original letters exactly once.
 */

class Solution
{
public:
    bool isAnagram(const std::string& s, const std::string& t)
    {
        if (s.size() != t.size())
            return false;

        std::unordered_map<char, int> freq;
        for (const auto& c : s) {
            freq[c]++;
        }
        for (const auto& c : t) {
            if (--freq[c] < 0)
                return false;
        }
        return true;
    }
};