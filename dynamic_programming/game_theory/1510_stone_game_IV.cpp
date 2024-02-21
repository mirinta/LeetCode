#include <vector>

/**
 * Alice and Bob take turns playing a game, with Alice starting first.
 *
 * Initially, there are n stones in a pile. On each player's turn, that player makes a move
 * consisting of removing any non-zero square number of stones in the pile.
 *
 * Also, if a player cannot make a move, he/she loses the game.
 *
 * Given a positive integer n, return true if and only if Alice wins the game otherwise return
 * false, assuming both players play optimally.
 *
 * ! 1 <= n <= 10^5
 */

class Solution
{
public:
    bool winnerSquareGame(int n)
    {
        std::vector<int> memo(n + 1, -1);
        return dp(memo, n);
    }

private:
    // given the game with n stones, check whether the 1st action player wins
    bool dp(std::vector<int>& memo, int n)
    {
        if (n == 0)
            return false;

        if (memo[n] != -1)
            return memo[n];

        for (int x = 1; x * x <= n; ++x) {
            // current player wins if his opponent can't win in the next game
            if (!dp(memo, n - x * x))
                return memo[n] = 1;
        }
        return memo[n] = 0;
    }
};