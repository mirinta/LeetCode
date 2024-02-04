#include <string>
#include <unordered_map>

/**
 * Given two strings "s" and "t" of lengths "m" and "n" respectively, return the minimum window
 * substring of "s" such that every character in "t" (including duplicates) is included in the
 * window. If there is no such substring, return the empty string "".
 *
 * ! m == s.length
 * ! n == t.length
 * ! 1 <= m, n <= 10^5
 * ! s and t consist of uppercase and lowercase English letters.
 */

class Solution
{
public:
    std::string minWindow(std::string s, std::string t)
    {
        if (t.size() > s.size())
            return {};

        std::unordered_map<char, int> map;
        for (const auto& c : t) {
            map[c]++;
        }
        const int m = s.size();
        int unique = 0;
        int minLength = INT_MAX;
        int minStart = -1;
        for (int left = 0, right = 0; right < m; ++right) {
            if (map.count(s[right]) && --map[s[right]] == 0) {
                unique++;
            }
            while (unique == map.size()) {
                if (minLength > right - left + 1) {
                    minLength = right - left + 1;
                    minStart = left;
                }
                if (map.count(s[left]) && ++map[s[left]] > 0) {
                    unique--;
                }
                left++;
            }
        }
        return minLength == INT_MAX ? "" : s.substr(minStart, minLength);
    }
};
