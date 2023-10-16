#include <string>
#include <vector>

/**
 * Given two strings word1 and word2, return the minimum number of steps required to make word1 and
 * word2 the same.
 *
 * In one step, you can delete exactly one character in either string.
 *
 * ! 1 <= word1.length, word2.length <= 500
 * ! word1 and word2 consist of only lowercase English letters.
 */

class Solution
{
public:
    int minDistance(const std::string& word1, const std::string& word2)
    {
        return approach2(word1, word2);
        // approach3: let L = length of the longest common sequence of word1 and word2
        // answer = word1.size() - L + word2.size() - L
    }

private:
    // DP with space optimization
    int approach2(const std::string& s1, const std::string& s2)
    {
        const int m = s1.size();
        const int n = s2.size();
        std::vector<int> dp(1 + n);
        for (int j = 0; j <= n; ++j) {
            dp[j] = j;
        }
        auto prev = dp;
        for (int i = 1; i <= m; ++i) {
            prev = dp;
            dp[0] = i;
            for (int j = 1; j <= n; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[j] = prev[j - 1];
                } else {
                    dp[j] = 1 + std::min(prev[j], dp[j - 1]);
                }
            }
        }
        return dp[n];
    }

    // DP
    int approach1(const std::string& s1, const std::string& s2)
    {
        const int m = s1.size();
        const int n = s2.size();
        // dp[i][j] = min num of steps to make s1[0:i) and s2[0:j) the same
        // base cases:
        // - dp[0][0] = 0
        // - dp[i>0][0] = i, delete all characters of s1[0:i)
        // - dp[0][j>0] = j, delete all characters of s2[0:j)
        std::vector<std::vector<int>> dp(1 + m, std::vector<int>(1 + n, INT_MAX));
        dp[0][0] = 0;
        for (int i = 1; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int j = 1; j <= n; ++j) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + std::min(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};
