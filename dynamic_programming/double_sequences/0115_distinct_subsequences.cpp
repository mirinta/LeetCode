#include <vector>
#include <string>

/**
 * Given two strings "s" and "t", return the number of distinct subsequences of "s" which equals
 * "t".
 *
 * The test cases are generated so that the answer fits on a 32-bits signed integer.
 */

class Solution
{
public:
    int numDistinct(const std::string& s, const std::string& t)
    {
        if (s.empty() || t.empty())
            return 0;

        const auto m = s.size();
        const auto n = t.size();
        if (m < n)
            return 0;

        // dp table:
        // dp[i][j] = numDistinct of s[0: i) which equals to t[0: j),
        // - where i is in range [0, m], and j is in range [0, n]

        // boundary 1: for each i, dp[i][0] = 1
        // - if j = 0, t is an empty string
        // - "" (empty string) is the only subsequence of s that equals t.

        // boundary 2: for each j, dp[0][j] = 0
        // - if i = 0, s is an empty string
        // - there is no subsequence of s that equals t.

        // initialize the dp table with 0, boundary 2 is achieved
        std::vector<std::vector<size_t>> dp(m + 1, std::vector<size_t>(n + 1, 0));
        // initialize boundary 1
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = 1;
        }
        // start iteration, i in range [1, m], j in range [1, n]
        // note that both i and j start from 1,
        // when accessing character of s and t, use s[i - 1] and t[j - 1]
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] += dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};