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
 * ! strs[i] consists of lowercase English letters.
 */

class Solution
{
public:
    std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs)
    {
        if (strs.empty())
            return {};

        std::unordered_map<std::string, std::vector<std::string>> map;
        for (const auto& str : strs) {
            std::string key{str};
            std::sort(key.begin(), key.end());
            map[key].push_back(str);
        }
        std::vector<std::vector<std::string>> result;
        for (auto& pair : map) {
            result.push_back(std::move(pair.second));
        }
        return result;
    }

    // version 2: encoding
    // public:
    //     vector<vector<string>> groupAnagrams(vector<string>& strs) {
    //         if (strs.empty())
    //             return {};

    //         std::unordered_map<std::string, std::vector<std::string>> map;
    //         for (const auto& s : strs) {
    //             map[encode(s)].push_back(s);
    //         }
    //         std::vector<std::vector<std::string>> result;
    //         for (auto& pair : map) {
    //             result.push_back(std::move(pair.second));
    //         }
    //         return result;
    //     }

    // private:
    //     std::array<int, 26> letters;

    //     std::string encode(const std::string& str) {
    //         if (str.empty())
    //             return {};

    //         constexpr char k_a = 'a';
    //         std::fill(letters.begin(), letters.end(), 0);
    //         for (const auto& c : str) {
    //             letters[c - k_a]++;
    //         }
    //         std::string result;
    //         for (size_t i = 0; i < letters.size(); ++i) {
    //             if (letters[i] == 0)
    //                 continue;

    //             result.push_back(i + k_a);
    //             result.append(std::to_string(letters[i]));
    //         }
    //         return result;
    //     }
};
