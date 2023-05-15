#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given two string "s" and "p", return an array of all the start indicies of "p"'s anagrams in "s".
 * You may return the answer in any order.
 *
 * An anagram is a word or phase formed by rearranging the letters of a different word or phase,
 * typically using all the original letters exactly once.
 *
 * Example 1:
 * Input: s = "cbaebabacd", p = "abc"
 * Output: [0, 6], because s = {cba}eba{bac}d, "cba" and "bac" are anagrams of "abc".
 *
 * Example 2:
 * Input: s = "abab", p = "ab"
 * Output: [0, 1, 2]
 */

class Solution
{
public:
    // similar to LC 567
    std::vector<int> findAnagrams(const std::string& s, const std::string& p)
    {
        if (s.empty() || p.empty() || p.size() > s.size())
            return {};

        std::vector<int> result;
        // to check a substring is valid
        std::unordered_map<char, int> freq;
        for (const auto& c : p) {
            freq[c]++;
        }
        size_t counter = 0; // valid if counter = freq.size()
        // sliding window, characters in range [left, right)
        int left = 0;
        int right = 0;
        while (right < s.size()) {
            while (right - left < p.size()) {
                const auto& charRight = s[right++];
                if (freq.count(charRight) && --freq[charRight] == 0) {
                    counter++;
                }
            }
            if (counter == freq.size()) {
                result.push_back(left);
            }
            const auto& charLeft = s[left++];
            if (freq.count(charLeft) && freq[charLeft]++ == 0) {
                counter--;
            }
        }
        return result;
    }
};