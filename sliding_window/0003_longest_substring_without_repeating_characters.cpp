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
    int lengthOfLongestSubstring(std::string s) { return approach2(s); }

private:
    // time O(N), space O(N)
    int approach2(const std::string& s)
    {
        if (s.size() < 2)
            return s.size();

        int result = 0;
        std::unordered_map<char, int> map; // letter to index
        for (int i = 0, j = 0; i < s.size(); ++i) {
            if (map.count(s[i])) {
                j = std::max(j, map[s[i]] + 1);
            }
            map[s[i]] = i;
            result = std::max(result, i - j + 1);
        }
        return result;
    }

    // time O(N), space O(N)
    int approach1(const std::string& s)
    {
        if (s.size() < 2)
            return s.size();

        int result = 0;
        int left = 0;
        int right = 0;
        std::unordered_map<char, int> map; // letter to frequency
        // sliding window, elements in range [left, right)
        while (right < s.size()) {
            const auto c = s[right++];
            map[c]++;
            while (map[c] > 1) {
                map[s[left++]]--;
            }
            result = std::max(result, right - left);
        }
        return result;
    }
};