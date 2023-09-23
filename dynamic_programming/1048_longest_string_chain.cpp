#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given an array of words where each word consists of lowercase English letters.
 *
 * wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA
 * without changing the order of the other characters to make it equal to wordB.
 *
 * - For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
 *
 * A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a
 * predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a
 * word chain with k == 1.
 *
 * Return the length of the longest possible word chain with words chosen from the given list of
 * words.
 *
 * ! 1 <= words.length <= 1000
 * ! 1 <= words[i].length <= 16
 * ! words[i] only consists of lowercase English letters.
 */

class Solution
{
public:
    int longestStrChain(std::vector<std::string>& words)
    {
        std::sort(words.begin(), words.end(),
                  [](const auto& s1, const auto& s2) { return s1.size() < s2.size(); });
        // dp[word] = longest length of word chain that ends with "word"
        int result = 1;
        std::unordered_map<std::string, int> dp;
        for (const auto& word : words) {
            if (!dp.count(word)) {
                dp[word] = 1;
            }
            for (int i = 0; i < word.size(); ++i) {
                std::string predecessor(word);
                predecessor.erase(i, 1);
                if (dp.count(predecessor)) {
                    dp[word] = std::max(dp[predecessor] + 1, dp[word]);
                    result = std::max(result, dp[word]);
                }
            }
        }
        return result;
    }
};