#include <string>
#include <vector>

/**
 * There is a strange printer with the following two special properties:
 *
 * - The printer can only print a sequence of the same character each time.
 *
 * - At each turn, the printer can print new characters starting from and ending at any place and
 * will cover the original existing characters.
 *
 * Given a string s, return the minimum number of turns the printer needed to print it.
 *
 * ! 1 <= s.length <= 100
 * ! s consists of lowercase English letters.
 */

class Solution
{
public:
    int strangePrinter(std::string s)
    {
        // dp[i][j] = min num of turns to print s[i:j]
        const int n = s.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, INT_MAX / 2));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
        }
        for (int length = 2; length <= n; ++length) {
            for (int i = 0; i + length - 1 < n; ++i) {
                const int j = i + length - 1;
                // case 1: print single s[i]
                dp[i][j] = std::min(dp[i][j], 1 + dp[i + 1][j]);
                // case 2: s[i] = s[j], then s[j] can be printed when processing s[i:j-1]
                if (s[i] == s[j]) {
                    dp[i][j] = std::min(dp[i][j], dp[i][j - 1]);
                }
                // case 3: s[i] = s[k], then s[k] can be printed when processing s[i:k-1]
                for (int k = i + 1; k < j; ++k) {
                    if (s[i] == s[k]) {
                        dp[i][j] = std::min(dp[i][j], dp[i][k - 1] + dp[k + 1][j]);
                    }
                }
            }
        }
        return dp[0][n - 1];
    }
};