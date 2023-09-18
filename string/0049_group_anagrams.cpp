#include <algorithm>
#include <array>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given an array of strings "strs", group the anagrams together. You can return the answer in any
 * order.
 *
 * An anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
 * typically using all the original letters exactly once.
 *
 * ! 1 <= strs.length <= 10^4
 * ! 0 <= strs[i].length <= 100
 * ! strs[i] consists of lowercase English letters.
 */

class Solution
{
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs)
    {
        return approach2(strs);
    }

private:
    // time O(NK), space O(NK)
    // - N = strs.size(), K = maximum length of strs[i]
    std::vector<std::vector<std::string>> approach2(const std::vector<std::string>& strs)
    {
        std::vector<std::vector<std::string>> result;
        std::unordered_map<std::string, std::vector<std::string>> map;
        for (const auto& s : strs) {
            map[encode(s)].push_back(s);
        }
        for (auto& [key, anagrams] : map) {
            result.push_back(std::move(anagrams));
        }
        return result;
    }

    std::string encode(const std::string& s)
    {
        // counting sort
        constexpr int R = 26;
        std::array<int, R> count{0};
        for (const auto& c : s) {
            count[c - 'a']++;
        }
        std::string result;
        for (int i = 0; i < R; ++i) {
            if (count[i] > 0) {
                result.push_back(i + 'a');
                result.push_back(count[i]);
            }
        }
        return result;
    }

    // time O(NKlogK), space O(NK)
    // - N = strs.size(), K = maximum length of strs[i]
    std::vector<std::vector<std::string>> approach1(const std::vector<std::string>& strs)
    {
        std::vector<std::vector<std::string>> result;
        std::unordered_map<std::string, std::vector<std::string>> map;
        for (const auto& s : strs) {
            std::string key(s);
            std::sort(key.begin(), key.end());
            map[key].push_back(s);
        }
        result.reserve(map.size());
        for (auto& [key, anagrams] : map) {
            result.push_back(std::move(anagrams));
        }
        return result;
    }
};
