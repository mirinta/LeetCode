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
        std::unordered_map<char, int> map;
        for (const auto& c : t) {
            map[c]++;
        }
        int minLength = INT_MAX;
        int start = -1;
        for (int left = 0, right = 0, unique = 0; right < s.size(); ++right) {
            if (map.count(s[right]) && --map[s[right]] == 0) {
                unique++;
            }
            while (unique == map.size()) {
                if (right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    start = left;
                }
                if (map.count(s[left])) {
                    unique += map[s[left]] == 0 ? -1 : 0;
                    map[s[left]]++;
                }
                left++;
            }
        }
        return minLength == INT_MAX ? "" : s.substr(start, minLength);
    }
};
