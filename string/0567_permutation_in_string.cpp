#include <string>
#include <unordered_map>

/**
 * Given two strings "s1" and "s2", return "true" if "s2" contains a permutation of "s1", or "false"
 * otherwise.
 *
 * In other words, return "true" if one of "s1"'s permutations is the substring of "s2".
 *
 * Example 1:
 * Input: s1 = "ab", s2 = "eidbaoooo"
 * Output: true, because s2 = eid{ba}oooo, "ba" is a permutation of "s1"
 *
 * Example:
 * Input: s1 = "ab", s2 = "eidboaooo"
 * Output: false
 */

class Solution
{
public:
    bool checkInclusion(std::string s1, std::string s2)
    {
        if (s1.empty() || s2.empty() || s1.size() > s2.size())
            return false;

        // to check a substring is valid
        std::unordered_map<char, int> freq;
        for (const auto& c : s1) {
            freq[c]++;
        }
        size_t counter = 0;
        // sliding window, characters in range [left, right)
        int left = 0;
        int right = 0;
        while (right < s2.size()) {
            while (right - left < s1.size()) {
                const auto charRight = s2[right++];
                if (freq.count(charRight) && --freq[charRight] == 0) {
                    counter++;
                }
            }
            if (counter == freq.size())
                return true;

            const auto charLeft = s2[left++];
            if (freq.count(charLeft) && freq[charLeft]++ == 0) {
                counter--;
            }
        }
        return false;
    }
};