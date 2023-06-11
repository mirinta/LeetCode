#include <string>
#include <vector>

/**
 * Given two strings "word1" and "word2", return the minimum number of steps required to make
 * "word1" and "word2" the same.
 *
 * In one step, you can delete exactly one charater in either string.
 *
 * Example:
 * Input: word1 = "sea", word2 = "eat"
 * Output: 2
 * Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
 */

class Solution
{
public:
    int minDistance(std::string word1, std::string word2)
    {
        // word1 = "sea", word2 = "eat"
        // after N deletions: word1 = word2 = "ea"
        // "ea" is the longest common subsequence of "sea" and "eat"!
        const auto n = longestCommonSubsequence(word1, word2);
        return word1.size() - n + word2.size() - n;
    }

private:
    // same as LC 1143
    int longestCommonSubsequence(const std::string& word1, const std::string& word2)
    {
        const auto m = word1.size();
        const auto n = word2.size();
        // dp[i][j] = length of longest common subsequence of word1[0:i) and word2[0:j)
        // base cases:
        // dp[i][0] = 0, word2 is empty, no common subsequence
        // dp[0][j] = 0, word1 is empty, no common subsequence
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};