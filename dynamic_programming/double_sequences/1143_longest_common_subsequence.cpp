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
 *
 * ! 1 <= text1.length, text2.length <= 1000
 * ! text1 and text2 consist of only lowercase English characters.
 */

class Solution
{
public:
    int longestCommonSubsequence(std::string text1, std::string text2)
    {
        return approach2(text1, text2);
    }

private:
    // DP with space optimization, time O(MN), space O(N)
    // - M and N are the length of s1 and s2, respectively
    int approach2(const std::string& s1, const std::string& s2)
    {
        const int m = s1.size();
        const int n = s2.size();
        std::vector<int> dp(n + 1, 0);
        for (int i = 1; i <= m; ++i) {
            auto prev = dp;
            for (int j = 1; j <= n; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[j] = 1 + prev[j - 1];
                } else {
                    dp[j] = std::max(prev[j], dp[j - 1]);
                }
            }
        }
        return dp[n];
    }

    // DP, time O(MN), space O(MN)
    // - M and N are the length of s1 and s2, respectively
    int approach1(const std::string& s1, const std::string& s2)
    {
        const int m = s1.size();
        const int n = s2.size();
        // dp[i][j] = length of LCS of s1[0:i) and s2[0:j)
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};
