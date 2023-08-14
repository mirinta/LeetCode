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
    bool isInterleave(std::string s1, std::string s2, std::string s3)
    {
        return approach2(s1, s2, s3);
    }

private:
    // 1D-DP, time O(MN), space O(N)
    bool approach2(const std::string& s1, const std::string& s2, const std::string& s3)
    {
        if (s1.empty() || s2.empty())
            return s2 == s3 || s1 == s3;

        const int m = s1.size();
        const int n = s2.size();
        if (m + n != s3.size())
            return false;

        std::vector<bool> dp(n + 1, false);
        std::vector<bool> iMinus1(n + 1, false);
        iMinus1[0] = true;
        for (int j = 1; j <= n; ++j) {
            iMinus1[j] = iMinus1[j - 1] && (s2[j - 1] == s3[j - 1]);
        }
        for (int i = 1; i <= m; ++i) {
            dp[0] = iMinus1[0] && (s1[i - 1] == s3[i - 1]);
            for (int j = 1; j <= n; ++j) {
                if ((s3[i + j - 1] == s1[i - 1]) && iMinus1[j]) {
                    dp[j] = true;
                } else if ((s3[i + j - 1] == s2[j - 1]) && dp[j - 1]) {
                    dp[j] = true;
                } else {
                    dp[j] = false;
                }
            }
            iMinus1 = dp;
        }
        return dp[n];
    }

    // 2D-DP, time O(MN), space O(MN)
    bool approach1(const std::string& s1, const std::string& s2, const std::string& s3)
    {
        if (s1.empty() || s2.empty())
            return s2 == s3 || s1 == s3;

        const int m = s1.size();
        const int n = s2.size();
        if (m + n != s3.size())
            return false;

        // dp[i][j] = s3[0:i+j) can be formed by an interleaving of s1[0:i) and s2[0:j)
        std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
        // base case:
        // - dp[0][0] = true
        // - dp[i][0] = true if s1[0:i] == s3[0:i]
        // - dp[0][j] = true if s2[0:j] == s3[0:j]
        dp[0][0] = true;
        for (int i = 1; i <= m; ++i) {
            dp[i][0] = dp[i - 1][0] && (s1[i - 1] == s3[i - 1]);
        }
        for (int j = 1; j <= n; ++j) {
            dp[0][j] = dp[0][j - 1] && (s2[j - 1] == s3[j - 1]);
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // X X X i
                // X X j
                // X X X X X i+j
                if ((s3[i + j - 1] == s1[i - 1]) && dp[i - 1][j]) {
                    dp[i][j] = true;
                } else if ((s3[i + j - 1] == s2[j - 1]) && dp[i][j - 1]) {
                    dp[i][j] = true;
                } else {
                    dp[i][j] = false;
                }
            }
        }
        return dp[m][n];
    }
};