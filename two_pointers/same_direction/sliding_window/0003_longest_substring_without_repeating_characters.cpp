#include <string>
#include <unordered_map>

/**
 * Given a string "s", find the length of the longest substring without repeating characters.
 *
 * ! 0 <= s.length <= 5 * 10^4
 * ! s consists of English letters, digits, symbols and spaces.
 */

class Solution
{
public:
    int lengthOfLongestSubstring(std::string s) { return approach1(s); }

private:
    // time O(N), space O(N)
    int approach2(const std::string& s)
    {
        const int n = s.size();
        if (n <= 1)
            return n;

        int result = 0;
        std::unordered_map<char, int> map; // letter to its last occurrence index
        for (int i = 0, j = 0; i < n; ++i) {
            // ... j j+1 ... i ...
            // if s[i] == s[j], then s[j+1:i] is what we want
            if (map.count(s[i])) {
                j = std::max(j, map[s[i]] + 1);
            }
            result = std::max(result, i - j + 1);
            map[s[i]] = i;
        }
        return result;
    }

    // sliding window, time O(N), space O(N)
    int approach1(const std::string& s)
    {
        const int n = s.size();
        if (n <= 1)
            return n;

        int result = 0;
        std::unordered_map<char, int> map; // letter to frequency
        for (int left = 0, right = 0; right < n; ++right) {
            const auto letter = s[right];
            map[letter]++;
            while (map[letter] > 1) {
                map[s[left]]--;
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};
