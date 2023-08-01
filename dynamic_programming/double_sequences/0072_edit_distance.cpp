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
    int approach2(const std::string& word1, const std::string& word2)
    {
        // DP with space optimization
        if (word1.empty())
            return word2.size();

        const int m = word1.size();
        const int n = word2.size();
        std::vector<int> iMinus1(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            iMinus1[i] = i;
        }
        std::vector<int> dp(n + 1, 0);
        for (int i = 1; i <= m; ++i) {
            dp[0] = i;
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[j] = iMinus1[j - 1];
                    continue;
                }
                const int insertion = dp[j - 1] + 1;
                const int swap = iMinus1[j - 1] + 1;
                const int deletion = iMinus1[j] + 1;
                dp[j] = std::min({insertion, swap, deletion});
            }
            iMinus1 = dp;
        }
        return dp[n];
    }

    int approach1(const std::string& word1, const std::string& word2)
    {
        const int m = word1.size();
        const int n = word2.size();
        // dp[i][j] = min distance to covert word1[0:i) to word2[0:j)
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        // base cases:
        // dp[0][0] = 0, both word1 and word2 are empty, no operation
        // dp[0][j] = j, word1 is empty, insert all characters of word2 to word1
        // dp[i][0] = i, word2 is empty, delete all characters of word1
        for (int j = 1; j <= n; ++j) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // X X X i
                // Y Y Y j
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                    continue;
                }
                // insert a new character after i:
                // X X X i
                // X X X X j
                const int insertion = dp[i][j - 1] + 1;
                // replace i with another character:
                // X X X i
                // X X X j
                const int replacement = dp[i - 1][j - 1] + 1;
                // delete i:
                // X X X X i
                // X X X j
                const int deletion = dp[i - 1][j] + 1;
                dp[i][j] = std::min({insertion, replacement, deletion});
            }
        }
        return dp[m][n];
    }
};
