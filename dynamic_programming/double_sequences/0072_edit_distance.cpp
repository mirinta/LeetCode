#include <string>
#include <vector>

/**
 * Given two strings "word1" and "word2", return the minimum number of operations required to
 * convert "word1" to "word2".
 *
 * You have the following three operations permitted on a word:
 *
 * - Insert a character
 *
 * - Delete a character
 *
 * - Replace a character
 *
 * ! 0 <= word1.length, word2.length <= 500
 * ! word1 and word2 consist of lowercase English letters.
 */

class Solution
{
public:
    int minDistance(std::string word1, std::string word2) { return approach2(word1, word2); }

private:
    // DP with space optimization, time O(MN), space O(N)
    int approach2(const std::string& word1, const std::string& word2)
    {
        const int m = word1.size();
        const int n = word2.size();
        std::vector<int> dp(n + 1, 0);
        for (int j = 0; j <= n; ++j) {
            dp[j] = j;
        }
        auto prev = dp;
        for (int i = 1; i <= m; ++i) {
            prev = dp;
            dp[0] = i;
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[j] = prev[j - 1];
                    continue;
                }
                const int replace = prev[j - 1] + 1;
                const int remove = prev[j] + 1;
                const int insert = dp[j - 1] + 1;
                dp[j] = std::min({replace, remove, insert});
            }
        }
        return dp[n];
    }

    // DP, time O(MN), space O(MN)
    int approach1(const std::string& word1, const std::string& word2)
    {
        // dp[i][j] = min num of operations to convert word1[0:i) to word2[0:j)
        // base cases:
        // - dp[0][0] = 0
        // - dp[i][0] = i, remove characters
        // - dp[0][j] = j, insert characters
        const int m = word1.size();
        const int n = word2.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                    continue;
                }
                // operation1: replace i with a new character
                // X X i
                // X X j
                const int replace = dp[i - 1][j - 1] + 1;
                // operation2: remove i
                // X X X i
                // X X j
                const int remove = dp[i - 1][j] + 1;
                // operation3: insert a new character at i
                // X X i
                // X X X j
                const int insert = dp[i][j - 1] + 1;
                dp[i][j] = std::min({replace, remove, insert});
            }
        }
        return dp[m][n];
    }
};
