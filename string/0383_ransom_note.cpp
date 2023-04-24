#include <string>
#include <unordered_map>

/**
 * Given two strings "ransomNote" and "magazine", return "true" if "ransomNote" can be constructed
 * by using the letters from "magazine" and "false" otherwise.
 *
 * Each letter in "magazine" can only be used once in "ransomNote".
 */

class Solution
{
public:
    bool canConstruct(const std::string& ransomNote, const std::string& magazine)
    {
        std::unordered_map<char, size_t> freq;
        for (const auto& c : magazine) {
            freq[c]++;
        }
        for (const auto& c : ransomNote) {
            if (!freq.count(c) || freq[c] == 0)
                return false;

            freq[c]--;
        }
        return true;
    }
};