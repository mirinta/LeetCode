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
        std::unordered_map<char, int> map; // frequency of t[i]
        for (const auto& c : t) {
            map[c]++;
        }
        int minStart = 0;
        int minLength = INT_MAX;
        int left = 0;
        int right = 0;
        int count = 0; // count the num of valid characters
        // sliding window, characters in range [left, right)
        while (right < s.size()) {
            // expand the window size to find a feasible solution
            const auto& c1 = s[right++];
            if (map.count(c1) && --map[c1] == 0) {
                count++;
            }
            while (count == map.size()) {
                // update the optimal solution
                if (right - left < minLength) {
                    minStart = left;
                    minLength = right - left;
                }
                // shrink the window to find a better solution
                const auto& c2 = s[left++];
                if (map.count(c2) && map[c2]++ == 0) {
                    count--;
                }
            }
        }
        return minLength == INT_MAX ? "" : s.substr(minStart, minLength);
    }
};