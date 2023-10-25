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
        if (n < k)
            return 0;

        std::unordered_map<char, int> map; // letter to frequency
        int result = 0;
        for (int i = 0; i < n; ++i) {
            map[s[i]]++;
            if (i >= k && --map[s[i - k]] == 0) {
                map.erase(s[i - k]);
            }
            if (map.size() == k) {
                result++;
            }
        }
        return result;
    }
};