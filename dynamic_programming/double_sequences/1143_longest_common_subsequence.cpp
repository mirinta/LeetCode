#include <string>
#include <vector>

/**
 * Given two strings "text1" and "text2", return the length of their longest common subsequence. If
 * there is no common subsequence, return 0.
 *
 * A subsequence of a string is a new string generated from the original string with some characters
 * (can be none) deleted without changing the relative order of the remaining characters.
 *
 * - For example, "ace" is a subsequence of "abcde".
 *
 * A common subsequence of two strings is a subsequence that is common to both strings.
 */

class Solution
{
public:
    int longestCommonSubsequence(std::string text1, std::string text2)
    {
        // dp[i][j] = longestCommonSubsequence(text1[0: i), text2[0: j))
        const auto m = text1.size();
        const auto n = text2.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        // base cases:
        // - dp[i][0] = 0, text2 is empty, no common subsequence exists
        // - dp[0][j] = 0, text1 is empty, no common subsequence exists
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // if text1[i] = text2[j], it means the character is in the LCS
                // otherwise, we pick the max value of dp[i-1][j] and dp[i][j-1]
                // note that the ranges are [0, i) and [0, j),
                // when accessing characters, we need i - 1 and j - 1
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};