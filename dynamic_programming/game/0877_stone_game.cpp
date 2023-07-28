#include <vector>

/**
 * Alice and Bob play a game with piles of stones. There are an even number of piles arranged in a
 * row, and each pile has a positive integer number of stones piles[i].
 *
 * The objective of the game is to end with the most stones. The total number of stones across all
 * the piles is odd, so there are no ties.
 *
 * Alice and Bob take turns, with Alice starting first. Each turn, a player takes the entire pile of
 * stones either from the beginning or from the end of the row. This continues until there are no
 * more piles left, at which point the person with the most stones wins.
 *
 * Assuming Alice and Bob play optimally, return true if Alice wins the game, or false if Bob wins.
 *
 * ! 2 <= piles.length <= 500
 * ! piles.length is even.
 * ! 1 <= piles[i] <= 500
 * ! sum(piles[i]) is odd.
 */

class Solution
{
public:
    bool stoneGame(std::vector<int>& piles)
    {
        const int n = piles.size();
        // dp[i][j].first = a player's max score of playing with piles[i:j], and he plays first
        // dp[i][j].second = a player's max score of playing with piles[i:j], and he plays second
        std::vector<std::vector<std::pair<int, int>>> dp(
            n, std::vector<std::pair<int, int>>(n, {0, 0}));
        // base case: dp[i][i].first = piles[i], dp[i][i].second = 0
        // - because there's only one pile to choose
        for (int i = 0; i < n; ++i) {
            dp[i][i].first = piles[i];
            dp[i][i].second = 0;
        }
        for (int i = n - 2; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                const int pickLeft = piles[i] + dp[i + 1][j].second;
                const int pickRight = piles[j] + dp[i][j - 1].second;
                if (pickLeft > pickRight) {
                    dp[i][j].first = pickLeft;
                    dp[i][j].second = dp[i + 1][j].first;
                } else {
                    dp[i][j].first = pickRight;
                    dp[i][j].second = dp[i][j - 1].first;
                }
            }
        }
        return dp[0][n - 1].first > dp[0][n - 1].second;
    }
};