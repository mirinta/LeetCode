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
 */

class Solution
{
public:
    int minDistance(std::string word1, std::string word2)
    {
        // dp[i][j] = minDistance(word[0: i), word2[0: j))
        const auto m = word1.size();
        const auto n = word2.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        // base cases:
        // - dp[0][j], insert each char of word2[0: j), dp[0][j] = j
        // - dp[i][0], delete each char of word1[0: i), dp[i][0] = i
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
                // X X [X] i
                // Y Y [Y] j
                // three choices: insert, delete, and replace
                // - insert char at i: distance = dp[i][j - 1] + 1, move pointer j only
                // - delete char at i: distance = d[i - 1][j] + 1, move pointer i only
                // - replace char at i: distance = dp[i - 1][j - 1] + 1, move both pointers
                dp[i][j] = 1 + std::min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
            }
        }
        return dp[m][n];
    }
};