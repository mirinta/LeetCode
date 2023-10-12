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
        std::unordered_map<char, int> map; // char of t, frequency
        for (const auto& c : t) {
            map[c]++;
        }
        int minStart = 0;
        int minLength = INT_MAX;
        int left = 0;
        int right = 0;
        int count = 0; // num of unique characters of t
        while (right < s.size()) {
            const auto& charRight = s[right++];
            if (map.count(charRight) && --map[charRight] == 0) {
                count++;
            }
            while (count == map.size()) {
                // elements in range [left, right)
                if (right - left < minLength) {
                    minLength = right - left;
                    minStart = left;
                }
                const auto& charLeft = s[left++];
                if (map.count(charLeft) && map[charLeft]++ == 0) {
                    count--;
                }
            }
        }
        return minLength == INT_MAX ? "" : s.substr(minStart, minLength);
    }
};
