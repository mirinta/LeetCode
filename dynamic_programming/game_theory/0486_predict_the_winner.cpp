#include <vector>

/**
 * You are given an integer array nums. Two players are playing a game with this array: player 1 and
 * player 2.
 *
 * Player 1 and player 2 take turns, with player 1 starting first. Both players start the game with
 * a score of 0. At each turn, the player takes one of the numbers from either end of the array
 * (i.e., nums[0] or nums[nums.length - 1]) which reduces the size of the array by 1. The player
 * adds the chosen number to their score. The game ends when there are no more elements in the
 * array.
 *
 * Return true if Player 1 can win the game. If the scores of both players are equal, then player 1
 * is still the winner, and you should also return true. You may assume that both players are
 * playing optimally.
 *
 * ! 1 <= nums.length <= 20
 * ! 0 <= nums[i] <= 10^7
 */

class Solution
{
public:
    bool PredictTheWinner(std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i][j].first = a player's max score of playing with piles[i:j], and he plays first
        // dp[i][j].second = a player's max score of playing with piles[i:j], and he plays second
        // second
        std::vector<std::vector<std::pair<int, int>>> dp(
            n, std::vector<std::pair<int, int>>(n, {0, 0}));
        // base case:
        // - dp[i][i].first = nums[i], dp[i][i].second = 0,
        // - because there's only one number to choose
        for (int i = 0; i < n; ++i) {
            dp[i][i].first = nums[i];
            dp[i][i].second = 0;
        }
        for (int i = n - 2; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                // this player picks nums[i] in this round
                // next round is nums[i + 1, j], and the other player plays first
                const int pickLeft = nums[i] + dp[i + 1][j].second;
                // this player picks nums[j] in this round
                // next round is nums[i, j - 1], and the other player plays first
                const int pickRight = nums[j] + dp[i][j - 1].second;
                if (pickLeft > pickRight) {
                    dp[i][j].first = pickLeft;
                    dp[i][j].second = dp[i + 1][j].first;
                } else {
                    dp[i][j].first = pickRight;
                    dp[i][j].second = dp[i][j - 1].first;
                }
            }
        }
        return dp[0][n - 1].first >= dp[0][n - 1].second;
    }
};
