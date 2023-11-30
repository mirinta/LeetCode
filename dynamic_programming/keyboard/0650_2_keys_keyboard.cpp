#include <vector>

/**
 * There is only one character 'A' on the screen of a notepad. You can perform one of two operations
 * on this notepad for each step:
 *
 * - Copy All: You can copy all the characters present on the screen (a partial copy is not
 * allowed).
 *
 * - Paste: You can paste the characters which are copied last time.
 *
 * Given an integer n, return the minimum number of operations to get the character 'A' exactly n
 * times on the screen.
 *
 * ! 1 <= n <= 1000
 */

class Solution
{
public:
    int minSteps(int n)
    {
        // dp[i] = min operations to get exactly i 'A's
        // if we only copy one 'A', then we need at most n operations to get n 'A's
        // - it means dp[i] <= i
        // - corner case is dp[1] = 0
        // X X X X X X copy paste paste ... paste
        // |<--#A=j->|      |<-----x times----->|
        // |<---------------#A=i--------------->|
        // i = (x + 1) * j, x = i/j + 1
        // #operations = dp[j] + x + 1 = dp[j] + i/j
        std::vector<int> dp(1 + n, 0);
        dp[1] = 0;
        for (int i = 2; i <= n; ++i) {
            dp[i] = i;
            for (int j = i - 2; j >= 2; --j) {
                if (i % j == 0) {
                    dp[i] = std::min(dp[i], dp[j] + i / j);
                    break;
                }
            }
        }
        return dp[n];
    }
};