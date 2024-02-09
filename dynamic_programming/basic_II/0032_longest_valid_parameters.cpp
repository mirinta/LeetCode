#include <string>
#include <vector>

/**
 * Given a string containing just the characters '(' and ')', return the length of the longest valid
 * (well-formed) parentheses substring.
 *
 * ! 0 <= s.length <= 3 * 10^4
 * ! s[i] is '(', or ')'.
 */

class Solution
{
public:
    int longestValidParentheses(std::string s)
    {
        // dp[i] = length of the longest valid parentheses substring of s[0:i] ending at s[i]
        // a valid substring must have at least two elements and ends with ')'
        //
        // case 1: s[i-1] = '(' and s[i] = ')'
        // X X X ... X i-2 i-1 i
        //     |<---?--->|  (  )
        // we can add s[i-1:i] to the end of the longest valid substring ending at s[i-2]
        // thus, dp[i] = dp[i-2] + 2
        //
        // case 2: s[i-1] = ')' and s[i] = ')'
        // X X ... j-2 j-1 j ... X i-1 i
        //   |<--?-->|  ?  (.........) )
        //                 |<---L--->|
        // let L = dp[i-1] and j = i-L
        // we know s[j:i-1] is the longest valid substring ending at s[i-1]
        // if s[j-1] = '(', we can add s[j-1:i] to the end of
        // the longest valid substring ending at s[j-2]
        // thus, dp[i] = dp[j-2] + L + 2
        const int n = s.size();
        std::vector<int> dp(n, 0);
        int result = 0;
        for (int i = 1; i < n; ++i) {
            if (s[i] == '(')
                continue; // dp[i] = 0

            if (s[i - 1] == ')') {
                const int L = dp[i - 1];
                const int j = i - L;
                if (j - 1 >= 0 && s[j - 1] == '(') {
                    dp[i] = (j >= 2 ? dp[j - 2] : 0) + L + 2; // case 2
                }
            } else {
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2; // case 1
            }
            result = std::max(result, dp[i]);
        }
        return result;
    }
};