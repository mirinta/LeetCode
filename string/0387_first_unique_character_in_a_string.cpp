#include <string>
#include <unordered_map>

/**
 * Given a string s, find the first non-repeating character in it and return its index. If it does
 * not exist, return -1.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of only lowercase English letters.
 */

class Solution
{
public:
    int firstUniqChar(std::string s)
    {
        const int n = s.size();
        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            map[c]++;
        }
        for (int i = 0; i < n; ++i) {
            if (map[s[i]] == 1)
                return i;
        }
        return -1;
    }
};