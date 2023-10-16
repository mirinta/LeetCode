#include <string>
#include <vector>

/**
 * Given two strings s1 and s2, return the lowest ASCII sum of deleted characters to make two
 * strings equal.
 *
 * ! 1 <= s1.length, s2.length <= 1000
 * ! s1 and s2 consist of lowercase English letters.
 */

class Solution
{
public:
    int minimumDeleteSum(const std::string& s1, const std::string& s2) { return approach2(s1, s2); }

private:
    // DP with space optimization
    int approach2(const std::string& s1, const std::string& s2)
    {
        const int m = s1.size();
        const int n = s2.size();
        std::vector<int> dp(1 + n, 0);
        for (int j = 1; j <= n; ++j) {
            dp[j] = dp[j - 1] + s2[j - 1];
        }
        auto prev = dp;
        for (int i = 1; i <= m; ++i) {
            prev = dp;
            dp[0] = prev[0] + s1[i - 1];
            for (int j = 1; j <= n; ++j) {
                const auto& c1 = s1[i - 1];
                const auto& c2 = s2[j - 1];
                if (c1 == c2) {
                    dp[j] = prev[j - 1];
                } else {
                    dp[j] = std::min(c1 + prev[j], c2 + dp[j - 1]);
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
        // dp[i][j] = min ASCII sum of deleted characters to make s1[0:i) and s2[0:j) the same
        // base cases:
        // - dp[0][0] = 0
        // - dp[i>0][0] = ASCII sum of s1[0:i), i.e., delete all characters of s1[0:i)
        // - dp[0][j>0] = ASCII sum of s2[0:j), i.e., delete all characters of s2[0:j)
        std::vector<std::vector<int>> dp(1 + m, std::vector<int>(1 + n, INT_MAX));
        dp[0][0] = 0;
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
                if (c1 == c2) {
                    dp[i][j] = dp[i - 1][j - 1]; // both c1 and c2 are not deleted
                } else {
                    // delete either c1 or c2
                    dp[i][j] = std::min(c1 + dp[i - 1][j], c2 + dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};
