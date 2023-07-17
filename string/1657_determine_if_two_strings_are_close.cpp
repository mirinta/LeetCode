#include <algorithm>
#include <array>
#include <string>
#include <unordered_map>

/**
 * Two strings are considered close if you can attain one from the other using the following
 * operations:
 *
 * - Operation 1: Swap any two existing characters.
 * For example, abcde -> aecdb
 *
 * - Operation 2: Transform every occurrence of one existing character into another existing
 * character, and do the same with the other character.
 *
 * For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's) You can use
 * the operations on either string as many times as necessary.
 *
 * Given two strings, word1 and word2, return true if word1 and word2 are close, and false
 * otherwise.
 *
 * ! 1 <= word1.length, word2.length <= 10^5
 * ! word1 and word2 contain only lowercase English letters.
 */

class Solution
{
public:
    bool closeStrings(const std::string& word1, const std::string& word2)
    {
        if (word1.size() != word2.size())
            return false;

        constexpr int kNumOfLetters = 26;
        std::array<int, kNumOfLetters> letterFrequency1 = {0};
        for (const auto& c : word1) {
            letterFrequency1[c - 'a']++;
        }
        std::array<int, kNumOfLetters> letterFrequency2 = {0};
        for (const auto& c : word2) {
            if (letterFrequency1[c - 'a'] == 0)
                return false;

            letterFrequency2[c - 'a']++;
        }
        std::sort(letterFrequency1.begin(), letterFrequency1.end());
        std::sort(letterFrequency2.begin(), letterFrequency2.end());
        for (int i = 0; i < kNumOfLetters; ++i) {
            if (letterFrequency1[i] != letterFrequency2[i])
                return false;
        }
        return true;
    }

private:
    bool approach1(const std::string& word1, const std::string& word2)
    {
        // both operations does not create new characters
        // thus, word1 and word2 must have the same length
        if (word1.size() != word2.size())
            return false;

        std::unordered_map<char, int> map1; // character to frequency of word1
        for (const auto& c : word1) {
            map1[c]++;
        }
        std::unordered_map<char, int> map2; // character to frequency of word2
        for (const auto& c : word2) {
            if (!map1.count(c))
                return false;

            map2[c]++;
        }
        std::unordered_map<int, int> map3; // frequency to frequency of word1
        for (const auto& [letter, freq] : map1) {
            map3[freq]++;
        }
        for (const auto& [letter, freq] : map2) {
            if (map3.count(freq) && map3[freq]-- == 1) {
                map3.erase(freq);
            }
        }
        return map3.empty();
    }
};