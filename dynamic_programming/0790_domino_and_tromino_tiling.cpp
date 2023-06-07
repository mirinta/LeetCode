#include <vector>

/**
 * You have two types of tiles: a 2x1 domino shape and a tromino shape. You may rotate these shapes.
 *
 * Given an integer n, return the number of ways to tile an 2xn board. Since the answer may be very
 * large, return it modulo 10^9 + 7.
 *
 * In a tiling, every square must be covered by a tile. Two tilings are different if an only if
 * there are two 4-directionally adjacent cells on the board such that exactly one of the tilings
 * has both squares occupied by a tile.
 */

class Solution
{
public:
    int numTilings(int n)
    {
        if (n <= 0)
            return 0;

        // dp[i][j] = number of ways to tile an 2xi board
        // - j is either 0, 1, or 2
        // - case 1: j = 0, both rows of the ith column are covered
        // - dp[i][0] = dp[i - 1][0] + dp[i - 2][0] + dp[i - 1][2] + dp[i - 1][1];
        // X X
        // X X
        // - case 2: j = 1, only the 1st row of the ith column is covered
        // - dp[i][0] = dp[i - 1][0] + dp[i - 2][0] + dp[i - 1][2] + dp[i - 1][1];
        // X X
        // X
        // - case 3: j = 2, only the 2nd row of the ith column is covered
        // - dp[i][2] = dp[i - 2][0] + dp[i - 1][1];
        // X
        // X X
        // - finally, case 2 and case 3 are the same
        std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(2, 0));
        dp[0][0] = 1;
        dp[1][0] = 1;
        constexpr int mod = 1e9 + 7;
        for (int i = 2; i <= n; ++i) {
            dp[i][0] = (dp[i - 1][0] + dp[i - 2][0] + 2 * dp[i - 1][1]) % mod;
            dp[i][1] = (dp[i - 2][0] + dp[i - 1][1]) % mod;
        }
        return dp[n][0];
    }
};