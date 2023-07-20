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
        // dp[i][j] = num of ways to tile an 2xi board
        // j = 0   j = 1   j = 2
        //  X X      X X     X
        //  X X      X       X X
        // j = 0 means both rows are covered
        // j = 1 means only the first row is covered
        // j = 2 means only the second row is covered
        constexpr int kMod = 1e9 + 7;
        std::vector<std::vector<long>> dp(n + 1, std::vector<long>(3, 0));
        dp[0][0] = 1;
        dp[1][0] = 1;
        for (int i = 2; i <= n; ++i) {
            // X X D    X X T    X T T    X D D
            // X X D    X T T    X X T    X D D
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2] + dp[i - 2][0]) % kMod;
            // X T T    X D D
            // X T      X X
            dp[i][1] = (dp[i - 2][0] + dp[i - 1][2]) % kMod;
            // X T      X X
            // X T T    X D D
            dp[i][2] = (dp[i - 2][0] + dp[i - 1][1]) % kMod;
        }
        return dp[n][0];
    }
};
