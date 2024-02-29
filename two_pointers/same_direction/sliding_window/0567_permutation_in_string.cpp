#include <array>
#include <string>

/**
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
 *
 * In other words, return true if one of s1's permutations is the substring of s2.
 *
 * ! 1 <= s1.length, s2.length <= 10^4
 * ! s1 and s2 consist of lowercase English letters.
 */

class Solution
{
public:
    bool checkInclusion(std::string s1, std::string s2)
    {
        const int n = s1.size();
        const int m = s2.size();
        std::array<int, 26> target{};
        for (const auto& c : s1) {
            target[c - 'a']++;
        }
        std::array<int, 26> count{};
        for (int left = 0, right = 0; right < m; ++right) {
            count[s2[right] - 'a']++;
            if (right - left + 1 > n) {
                count[s2[left] - 'a']--;
                left++;
            }
            if (right - left + 1 == n && count == target)
                return true;
        }
        return false;
    }
};