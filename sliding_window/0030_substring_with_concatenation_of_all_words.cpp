#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a string s and an array of strings words. All the strings of words are of the same
 * length.
 *
 * A concatenated substring in s is a substring that contains all the strings of any permutation of
 * words concatenated.
 *
 * - For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab",
 * "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated substring
 * because it is not the concatenation of any permutation of words.
 *
 * Return the starting indices of all the concatenated substrings in s. You can return the answer in
 * any order.
 *
 * ! 1 <= s.length <= 10^4
 * ! 1 <= words.length <= 5000
 * ! 1 <= words[i].length <= 30
 * ! s and words[i] consist of lowercase English letters.
 */

class Solution
{
public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words)
    {
        const int wordLength = words[0].size();
        const int windowLength = wordLength * words.size();
        if (s.size() < windowLength)
            return {};

        std::unordered_map<std::string, int> wordCount;
        for (const auto& word : words) {
            wordCount[word]++;
        }
        // [word_1 ... word_n] word_n+1 word_n+2 ...
        std::vector<int> result;
        for (int i = 0; i < wordLength; ++i) {
            std::unordered_map<std::string, int> map;
            int count = 0;
            for (int j = i; j + wordLength <= s.size(); j += wordLength) {
                if (j - i >= windowLength) {
                    const std::string out = s.substr(j - windowLength, wordLength);
                    map[out]--;
                    if (map[out] < wordCount[out]) {
                        count--;
                    }
                }
                const std::string in = s.substr(j, wordLength);
                map[in]++;
                if (map[in] <= wordCount[in]) {
                    count++;
                }
                if (count == words.size()) {
                    result.push_back(j - (words.size() - 1) * wordLength);
                }
            }
        }
        return result;
    }
};