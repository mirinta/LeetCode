#include <string>
#include <unordered_map>

/**
 * Given a string s and an integer k, return the number of substrings in s of length k with no
 * repeated characters.
 *
 * ! 1 <= s.length <= 10^4
 * ! s consists of lowercase English letters.
 * ! 1 <= k <= 10^4
 */

class Solution
{
public:
    int numKLenSubstrNoRepeats(std::string s, int k)
    {
        const int n = s.size();
        if (k > n)
            return 0;

        std::unordered_map<char, int> map;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            map[s[right]]++;
            if (right - left + 1 > k) {
                if (--map[s[left]] == 0) {
                    map.erase(s[left]);
                }
                left++;
            }
            if (right - left + 1 == k && map.size() == k) {
                result++;
            }
        }
        return result;
    }
};