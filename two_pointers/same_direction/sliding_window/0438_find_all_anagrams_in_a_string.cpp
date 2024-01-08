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
        if (s.size() < p.size())
            return {};

        const int n = s.size();
        std::unordered_map<char, int> map;
        for (const auto& c : p) {
            map[c]++;
        }
        std::vector<int> result;
        for (int left = 0, right = 0, unique = 0; right < n; ++right) {
            if (map.count(s[right]) && --map[s[right]] == 0) {
                unique++;
            }
            while (unique == map.size()) {
                if (right - left + 1 == p.size()) {
                    result.push_back(left);
                }
                if (map.count(s[left])) {
                    unique += map[s[left]] == 0 ? -1 : 0;
                    map[s[left]]++;
                }
                left++;
            }
        }
        return result;
    }
};
