#include <string>
#include <vector>

/**
 * Given a string "s", find the longest palindromic subsequence's length in "s".
 *
 * A subsequence is a sequence that can be derived from another sequence by deleting some or no
 * elements without changing the order of the remaining elements.
 *
 * Example:
 * Input: s = "bbbab"
 * Output: 4
 * Explanation: One possible longest palindromic subsequence is "bbbb".
 */

class Solution
{
public:
    int longestPalindromeSubseq(std::string s)
    {
        const auto n = s.size();
        if (n < 1)
            return n;

        // ... i [i+1 ... j-1] j ...
        //     ^               ^
        // dp[i][j] = length of LPS of s[i:j]
        // - if s[i] == s[j], both of them are in the LPS, then dp[i][j] = s[i+1:j-1] + 2
        // - otherwise, either s[i] or s[j] is in the LPS, or both of them are not in the LPS
        //   thus, dp[i][j] = max(dp[i+1][j], dp[i][j-1], dp[i+1][j-1]),
        //   dp[i+1][j-1] can be ignored, because its value is always <= one of the other two
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        // base case:
        // - if i = j, it means s[i:j] = s[i:i] has only one character, then dp[i][i] = 1
        // for-loop ranges: i from n-2 to 0, j from i+1 to n-1
        // - dp[i][j] is dependent on dp[i+1][j-1], dp[i][j-1], and dp[i+1][j]),
        //   it means larger i and smaller j must be calculated first
        // - s[i:j] should contain at least two characters,
        //   one character implies i=j which is the base case
        // in practice: let i starts from i-1 and initialize the base case
        for (int i = n - 1; i >= 0; --i) {
            dp[i][i] = 1;
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    dp[i][j] = 2 + dp[i + 1][j - 1];
                } else {
                    dp[i][j] = std::max(dp[i][j - 1], dp[i + 1][j]);
                }
            }
        }
        return dp[0][n - 1];
    }
};