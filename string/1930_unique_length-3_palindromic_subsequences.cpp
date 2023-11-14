#include <string>
#include <unordered_map>
#include <unordered_set>

/**
 * Given a string s, return the number of unique palindromes of length three that are a subsequence
 * of s.
 *
 * Note that even if there are multiple ways to obtain the same subsequence, it is still only
 * counted once.
 *
 * A palindrome is a string that reads the same forwards and backwards.
 *
 * A subsequence of a string is a new string generated from the original string with some characters
 * (can be none) deleted without changing the relative order of the remaining characters.
 *
 * - For example, "ace" is a subsequence of "abcde".
 *
 * ! 3 <= s.length <= 10^5
 * ! s consists of only lowercase English letters.
 */

class Solution
{
public:
    int countPalindromicSubsequence(std::string s)
    {
        // A x x x x x x x x x x A
        // ^ |<--count unique->| ^
        // first seen            last seen
        const int n = s.size();
        std::unordered_map<char, std::pair<int, int>> map;
        for (int i = 0; i < s.size(); ++i) {
            if (!map.count(s[i])) {
                map[s[i]] = {i, -1};
            } else {
                map[s[i]].second = i;
            }
        }
        int result = 0;
        for (const auto& info : map) {
            const auto& [firstSeen, lastSeen] = info.second;
            if (lastSeen - firstSeen - 1 <= 0)
                continue;

            std::unordered_set<char> set{s.begin() + firstSeen + 1, s.begin() + lastSeen};
            result += set.size();
        }
        return result;
    }
};
