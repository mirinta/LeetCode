#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given two string "s" and "p", return an array of all the start indicies of "p"'s anagrams in "s".
 * You may return the answer in any order.
 *
 * An anagram is a word or phase formed by rearranging the letters of a different word or phase,
 * typically using all the original letters exactly once.
 *
 * ! 1 <= s.length, p.length <= 3 * 10^4
 * ! s and p consist of lowercase English letters.
 */

class Solution
{
public:
    std::vector<int> findAnagrams(std::string s, std::string p)
    {
        std::unordered_map<char, int> map; // char of p, frequency
        for (const auto& c : p) {
            map[c]++;
        }
        int count = 0;
        int left = 0;
        int right = 0;
        std::vector<int> result;
        while (right < s.size()) {
            while (right - left + 1 <= p.size()) {
                const auto& charRight = s[right++];
                if (map.count(charRight) && --map[charRight] == 0) {
                    count++;
                }
            }
            if (count == map.size()) {
                result.push_back(left);
            }
            const auto& charLeft = s[left++];
            if (map.count(charLeft) && map[charLeft]++ == 0) {
                count--;
            }
        }
        return result;
    }
};
