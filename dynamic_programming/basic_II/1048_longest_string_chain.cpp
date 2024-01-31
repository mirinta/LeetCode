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
        // dp[word] = length of the longest word chain ending at word
        std::sort(words.begin(), words.end(),
                  [](const auto& s1, const auto& s2) { return s1.size() < s2.size(); });
        std::unordered_map<std::string, int> dp;
        int result = 0;
        for (const auto& word : words) {
            if (!dp.count(word)) {
                dp[word] = 1; // single word is a valid word chain with length = 1
            }
            for (int i = 0; i < word.size(); ++i) {
                auto expectedPredecessor = word;
                expectedPredecessor.erase(i, 1);
                if (dp.count(expectedPredecessor)) {
                    dp[word] = std::max(dp[expectedPredecessor] + 1, dp[word]);
                }
            }
            result = std::max(result, dp[word]);
        }
        return result;
    }
};