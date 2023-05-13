#include <vector>

/**
 * Given the integers "zero", "one", "low", and "high", we can construct a string by starting with
 * an empty string, and then at each step perform either of the following:
 *
 * - Append the character '0' "zero" times.
 *
 * - Append the character '1' "one" times.
 *
 * This can be performed by any number of times.
 *
 * A good string is a string constructed by the above process having a length between "low" and
 * "high" (inclusive).
 *
 * Return the number of different good strings that can be constructed satisfying these properties.
 * Since the answer can be large, return it modulo 10^9 + 7.
 */

class Solution
{
public:
    int countGoodStrings(int low, int high, int zero, int one)
    {
        constexpr int mod = 1e9 + 7;
        // dp[i] = number of good strings of length i
        std::vector<int> dp(high + 1, 0);
        dp[0] = 1;
        for (int length = 1; length <= high; ++length) {
            // case 1: length < #ones || length < #zeros, no option to choose
            if (length < one && length < zero)
                continue;
            // case 2: length >= #ones, we can append '1's
            // the previous length needs to be length - #ones
            if (length >= one) {
                dp[length] += dp[length - one];
            }
            // case 3: length >= #zeros, we can append '0's
            // the previous length needs to be length - #zeros
            if (length >= zero) {
                dp[length] += dp[length - zero];
            }
            dp[length] %= mod;
        }
        int result = 0;
        for (int i = low; i <= high; ++i) {
            result += dp[i];
            result %= mod;
        }
        return result;
    }
};