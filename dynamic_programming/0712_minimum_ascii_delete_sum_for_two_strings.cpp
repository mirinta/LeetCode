#include <string>
#include <vector>

/**
 * Given two strings "s1" and "s2", return the lowest ASCII sum of deleted characters to make two
 * strings equal.
 *
 * Example:
 * Input: s1 = "sea", s2 = "eat"
 * Output: 231
 * Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum. Deleting "t"
 * from "eat" adds 116 to the sum. At the end, both strings are equal, and 115 + 116 = 231 is the
 * minimum sum possible to achieve this.
 */

class Solution
{
public:
    int minimumDeleteSum(std::string s1, std::string s2)
    {
        // similar to LC 1143
        const auto m = s1.size();
        const auto n = s2.size();
        // dp[i][j] = minDeleteSum of s1[0:i) and s2[0:j)
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        // base cases:
        // - dp[i][0], s2[0:0) is empty, all characters of s1[0:i) need to be deleted
        // - dp[0][j], s1[0:0) is empty, all characters of s2[0:j) need to be deleted
        // - dp[0][0], both s1[0:0) and s2[0:0) are empty, no deletion
        for (int i = 1; i <= m; ++i) {
            dp[i][0] = dp[i - 1][0] + s1[i - 1];
        }
        for (int j = 1; j <= n; ++j) {
            dp[0][j] = dp[0][j - 1] + s2[j - 1];
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                const auto& c1 = s1[i - 1];
                const auto& c2 = s2[j - 1];
                // if c1 = c2 = c, it means c is part of the LCS, no deletion
                // otherwise, either c1 or c2 is not part of the LCS, delete one of them
                if (c1 == c2) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::min(c1 + dp[i - 1][j], c2 + dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};