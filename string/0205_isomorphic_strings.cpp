#include <string>
#include <unordered_map>
#include <unordered_set>

/**
 * Given two strings s and t, determine if they are isomorphic.
 *
 * Two strings s and t are isomorphic if the characters in s can be replaced to get t.
 *
 * All occurrences of a character must be replaced with another character while preserving the order
 * of characters. No two characters may map to the same character, but a character may map to
 * itself.
 *
 * ! 1 <= s.length <= 5 * 10^4
 * ! t.length == s.length
 * ! s and t consist of any valid ascii character.
 */

class Solution
{
public:
    bool isIsomorphic(std::string s, std::string t)
    {
        if (s.size() != t.size())
            return false;

        std::unordered_map<char, char> map;
        std::unordered_set<char> used;
        for (int i = 0; i < s.size(); ++i) {
            if (!map.count(s[i])) {
                if (used.count(t[i]))
                    return false;

                map[s[i]] = t[i];
                used.insert(t[i]);
                continue;
            }
            if (map[s[i]] != t[i])
                return false;
        }
        return true;
    }
};