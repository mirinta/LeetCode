#include <string>
#include <unordered_map>

/**
 * Given a string s, return true if a permutation of the string could form a palindrome and false
 * otherwise.
 *
 * ! 1 <= s.length <= 5000
 * ! s consists of only lowercase English letters.
 */

class Solution
{
public:
    bool canPermutePalindrome(std::string s)
    {
        std::unordered_map<char, int> map; // letter to frequency
        for (const auto& c : s) {
            map[c]++;
        }
        const bool isOddLength = s.size() % 2;
        int countOddFreq = 0;
        for (const auto& [c, freq] : map) {
            if (freq % 2) {
                countOddFreq++;
            }
            if (isOddLength && countOddFreq > 1)
                return false;

            if (!isOddLength && countOddFreq > 0)
                return false;
        }
        return true;
    }
};