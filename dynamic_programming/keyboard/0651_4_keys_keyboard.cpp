#include <vector>

/**
 * Imagine you have a special keyboard with the following keys:
 *
 * - A: Print one 'A' on the screen.
 *
 * - Ctrl-A: Select the whole screen.
 *
 * - Ctrl-C: Copy selection to buffer.
 *
 * - Ctrl-V: Print buffer on screen appending it after what has already been printed.
 *
 * Given an integer n, return the maximum number of 'A' you can print on the screen with at most n
 * presses on the keys.
 *
 * ! 1 <= n <= 50
 */

class Solution
{
public:
    int maxA(int n)
    {
        // dp[i] = max num of 'A' we can print on the screen by pressing i keys
        std::vector<int> dp(1 + n, 0);
        for (int i = 1; i <= n; ++i) {
            dp[i] = i; // press A
            for (int j = i - 1; j - 3 >= 1; --j) {
                // X X X j-3 CtrlA CtrlC j X X X X i
                //                       |<-CtrlV->|
                // #A = dp[j-3] + (i-j+1) * dp[j-3]
                dp[i] = std::max(dp[i], dp[j - 3] * (i - j + 2));
            }
        }
        return dp[n];
    }
};