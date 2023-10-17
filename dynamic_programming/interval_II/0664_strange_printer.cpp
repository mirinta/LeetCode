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
        const int n = s.size();
        // dp[i][j] = min num of turns to print s[i:j]
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, INT_MAX / 2));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
        }
        for (int i = n - 2; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                // case 1:
                // i [X X X X X X X j]
                // print one s[i] in this turn, and print s[i+1:j] in the next turn
                dp[i][j] = 1 + dp[i + 1][j];
                // case 2:
                // [i X X X] k [X X X j]
                // if s[k] == s[i], i < k < j
                // s[k] and s[i] can be printed in the same turn
                for (int k = i + 1; k < j; ++k) {
                    if (s[k] == s[i]) {
                        dp[i][j] = std::min(dp[i][j], dp[i][k - 1] + dp[k + 1][j]);
                    }
                }
                // case 3:
                // [i X X X X X X X] j
                // if s[i] == s[j],
                // s[j] and s[i] can be printed in the same turn
                if (s[i] == s[j]) {
                    dp[i][j] = std::min(dp[i][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][n - 1];
    }
};