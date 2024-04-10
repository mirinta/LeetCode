#include <unordered_map>
#include <string>

/**
 * Given a string s which consists of lowercase or uppercase letters, return the length of the
 * longest palindrome that can be built with those letters.
 *
 * Letters are case sensitive, for example, "Aa" is not considered a palindrome here.
 *
 * ! 1 <= s.length <= 2000
 * ! s consists of lowercase and/or uppercase English letters only.
 */

class Solution
{
public:
    int longestPalindrome(std::string s)
    {
        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            map[c]++;
        }
        bool hasOddFreq = false;
        int result = 0;
        for (const auto& [c, freq] : map) {
            if (freq % 2) {
                hasOddFreq = true;
                result += freq - 1;
            } else {
                result += freq;
            }
        }
        if (hasOddFreq) {
            result++;
        }
        return result;
    }
};