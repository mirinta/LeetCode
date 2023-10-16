#include <string>
#include <vector>

/**
 * Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.
 *
 * An interleaving of two strings s and t is a configuration where s and t are divided into n and m
 * substrings respectively, such that:
 *
 * - s = s1 + s2 + ... + sn
 *
 * - t = t1 + t2 + ... + tm
 *
 * - |n - m| <= 1
 *
 * - The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
 *
 * ! Note: a + b is the concatenation of strings a and b.
 *
 * ! 0 <= s1.length, s2.length <= 100
 * ! 0 <= s3.length <= 200
 * ! s1, s2, and s3 consist of lowercase English letters.
 */

class Solution
{
public:
    bool isInterleave(const std::string& s1, const std::string& s2, const std::string& s3)
    {
        return approach2(s1, s2, s3);
    }

private:
    // DP with space optimization
    bool approach2(const std::string& s1, const std::string& s2, const std::string& s3)
    {
        const int m = s1.size();
        const int n = s2.size();
        if (m + n != s3.size())
            return false;

        std::vector<bool> dp(1 + n);
        dp[0] = true;
        for (int j = 1; j <= n; ++j) {
            dp[j] = dp[j - 1] && (s2[j - 1] == s3[j - 1]);
        }
        for (int i = 1; i <= m; ++i) {
            dp[0] = dp[0] && (s1[i - 1] == s3[i - 1]);
            for (int j = 1; j <= n; ++j) {
                const auto& c1 = s1[i - 1];
                const auto& c2 = s2[j - 1];
                const auto& c3 = s3[i + j - 1];
                if (c1 == c3 && dp[j]) {
                    dp[j] = true;
                } else if (c2 == c3 && dp[j - 1]) {
                    dp[j] = true;
                } else {
                    dp[j] = false;
                }
            }
        }
        return dp[n];
    }

    // DP
    bool approach1(const std::string& s1, const std::string& s2, const std::string& s3)
    {
        const int m = s1.size();
        const int n = s2.size();
        if (m + n != s3.size())
            return false;

        // dp[i][j] = whether s3[0:i+j) is formed by an interleaving of s1[0:i) and s2[0:j)
        // base cases:
        // - dp[0][0] = true
        // - dp[i>0][0] = true if s1[0:i) == s3[0:i)
        // - dp[0][j>0] = true if s2[0:j) == s3[0:j)
        std::vector<std::vector<bool>> dp(1 + m, std::vector<bool>(1 + n, false));
        dp[0][0] = true;
        for (int i = 1; i <= m; ++i) {
            dp[i][0] = dp[i - 1][0] && (s1[i - 1] == s3[i - 1]);
        }
        for (int j = 1; j <= n; ++j) {
            dp[0][j] = dp[0][j - 1] && (s2[j - 1] == s3[j - 1]);
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // X X X X c1
                // X X X c2
                // X X X X X X X c3
                const auto& c1 = s1[i - 1];
                const auto& c2 = s2[j - 1];
                const auto& c3 = s3[i + j - 1];
                if (c1 == c3 && dp[i - 1][j]) {
                    dp[i][j] = true;
                } else if (c2 == c3 && dp[i][j - 1]) {
                    dp[i][j] = true;
                } else {
                    dp[i][j] = false;
                }
            }
        }
        return dp[m][n];
    }
};
