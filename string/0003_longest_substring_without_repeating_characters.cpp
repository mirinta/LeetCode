#include <string>
#include <unordered_map>

/**
 * Given a string "s", find the length of the longest substring without repeating characters.
 *
 * Example 1:
 * Input: s = "abcabcbb"
 * Output: 3, the answer if "abc", with the length of 3
 *
 * Example 2:
 * Input: s = "bbbbb"
 * Output: 1, the answer is "b", with the length of 1
 *
 * Example 3:
 * Input: s = "pwwkew"
 * Output: 3, the answer is "wke", with the length of 3
 */

class Solution
{
public:
    int lengthOfLongestSubstring(const std::string& s)
    {
        if (s.empty())
            return 0;

        // approach 1:
        // std::unordered_map<char, int> freq;
        // int maxLength = 0;
        // int left = 0;
        // int right = 0;
        // sliding window, characters in range [left, right)
        // while (right < s.size()) {
        //     // expand window until duplicate characters are found
        //     const auto& charRight = s[right++];
        //     freq[charRight]++;
        //     // shrink window until duplicates are eliminated
        //     while (freq[charRight] > 1) {
        //         freq[s[left++]]--;
        //     }
        //     if (right - left > maxLength) {
        //         maxLength = right - left;
        //     }
        // }
        // ------------------------------
        // approach 2:
        std::unordered_map<char, size_t> map; // record the last location of a character
        int maxLength = 0;
        for (size_t left = 0, right = 0; right < s.size(); ++right) {
            if (map.count(s[right])) {
                left = std::max(left, map[s[right]] + 1);
            }
            maxLength = std::max(
                maxLength, static_cast<int>(right - left + 1)); // characters in range [left, right]
            map[s[right]] = right;
        }
        return maxLength;
    }
};