#include <string>
#include <vector>

/**
 * Given a string "s". In one step you can insert any character at any index of the string.
 *
 * Return the minimum number of steps to make "s" palindrome.
 *
 * A Palindrome String is one that reads the same backward as well as forward.
 *
 * Example:
 * Input: s = "mbadm"
 * Output: 2
 * Explanation: String can be "mbdadbm" or "mdbabdm".
 *
 * Example:
 * Input: s = "leetcode"
 * Output: 5
 * Explanation: Inserting 5 characters the string becomes "leetcodocteel".
 */

class Solution
{
public:
    int minInsertions(std::string s)
    {
        // similar to LC 516
        // ... i [i+1 ... j-1] j ...
        //     ^               ^
        // dp[i][j] = minInsertions of s[i:j]
        // - if s[i] == s[j], the character is part of the palindrome, no insertion
        // - otherwise, insertion on either s[i+1:j] or s[i:j-1], pick the min and plus 1
        const auto n = s.size();
        if (n < 1)
            return 0;

        // base case: i == j implies s[i:j] contains only one character, then dp[i][j] = 0
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        for (int i = n - 2; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1];
                } else {
                    dp[i][j] = 1 + std::min(dp[i][j - 1], dp[i + 1][j]);
                }
            }
        }
        return dp[0][n - 1];
        // approach 2: return s.size() - longestPalindromeSubseq(s), see LC 516
    }
};