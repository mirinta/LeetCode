#include <string>
#include <vector>

/**
 * A message containing letters from A-Z can be encoded into numbers using the following mapping:
 *
 * 'A' -> "1"
 * 'B' -> "2"
 * ...
 * 'Z' -> "26"
 *
 * To decode an encoded message, all the digits must be grouped then mapped back into letters using
 * the reverse of the mapping above (there may be multiple ways). For example, "11106" can be mapped
 * into:
 *
 * - "AAJF" with the grouping (1 1 10 6)
 *
 * - "KJF" with the grouping (11 10 6)
 *
 * Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F' since "6" is
 * different from "06".
 *
 * Given a string "s" containing only digits, return the number of ways to decode it.
 *
 * The test cases are generated so that the answer fits in a 32-bit integer.
 *
 * ! s contains only digits and may contain leading zero(s).
 */

class Solution
{
public:
    int numDecodings(const std::string& s)
    {
        if (s.empty())
            return 0;

        const auto n = s.size();
        // dp[i] = num of ways to decode s[0:i)
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = s[0] == '0' ? 0 : 1;
        for (int i = 2; i <= n; ++i) {
            // X [X]
            // if s[i-1] is a valid non-zero number:
            if (s[i - 1] > '0') {
                dp[i] = dp[i - 1];
            }
            // [X X]
            // if s[i-2:i-1] can be grouped as a valid number:
            // - in range [10,19] or [20,26]
            if (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6')) {
                dp[i] += dp[i - 2];
            }
        }
        return dp[n];
    }
};