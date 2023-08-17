#include <algorithm>
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
    std::vector<std::vector<std::string>> approach2(const std::vector<std::string>& strs)
    {
        std::vector<int> freq(26, 0);
        auto encode = [&freq](const std::string& word) {
            std::fill(freq.begin(), freq.end(), 0);
            for (const auto& c : word) {
                freq[c - 'a']++;
            }
            std::string result;
            for (int i = 0; i < 26; ++i) {
                if (freq[i] == 0)
                    continue;

                result.push_back(i + 'a');
                result.push_back(freq[i]);
            }
            return result;
        };
        std::unordered_map<std::string, std::vector<std::string>> map;
        for (const auto& word : strs) {
            map[encode(word)].push_back(word);
        }
        std::vector<std::vector<std::string>> result;
        for (auto& [key, anagrams] : map) {
            result.push_back(std::move(anagrams));
        }
        return result;
    }

    std::vector<std::vector<std::string>> approach1(const std::vector<std::string>& strs)
    {
        std::unordered_map<std::string, std::vector<std::string>> map;
        for (const auto& word : strs) {
            std::string key(word);
            std::sort(key.begin(), key.end());
            map[key].push_back(word);
        }
        std::vector<std::vector<std::string>> result;
        for (auto& [key, anagrams] : map) {
            result.push_back(std::move(anagrams));
        }
        return result;
    }
};
