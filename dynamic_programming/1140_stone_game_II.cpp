#include <vector>

/**
 * Alice and Bob continue their games with piles of stones. There are a number of piles arranged in
 * a row, and each pile has a positive integer number of stones "piles[i]". The objective of the
 * game is to end with the most stones.
 *
 * Alice and Bob take turns, with Alice starting first. Initially, M = 1.
 *
 * On each player's turn, that player can take all the stones in the first X remaining piles, where
 * 1 <= X <= 2M. Then, we set M = max(M, X).
 *
 * The game continues until all the stones have been taken.
 *
 * Assuming Alice and Bob optimally, return the maximum number of stones Alice can get.
 *
 * ! 1 <= piles.length <= 100
 * ! 1 <= piles[i] <= 104
 */

class Solution
{
public:
    int stoneGameII(const std::vector<int>& piles)
    {
        if (piles.empty())
            return 0;

        if (piles.size() == 1)
            return piles[0];

        const auto n = piles.size();
        std::vector<int> suffixSum(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffixSum[i] = piles[i] + suffixSum[i + 1];
        }
        std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1)); // -1 means not calculated
        return dp(0, 1, memo, suffixSum, piles);
    }

private:
    int dp(int i, int M, std::vector<std::vector<int>>& memo, const std::vector<int>& suffixSum,
           const std::vector<int>& piles)
    {
        // standing at position i, this player needs to choose x, where x is in range [1, 2M]
        // for any x:
        // 1. this player takes x piles first, score1_x = sum(piles[i],...,piles[i+x-1])
        // 2. then, this player considers his opponent's strategy for the remaining piles:
        // - the opponent starts from position i+x with M = max(x,M)
        // - the opponent's max score is opponent_score = dp(i+x, max(x,M), piles)
        // - since this is a zero-sum game, and the total score in the remaining piles is
        //   remaining_score = sum(piles[i+x],...,piles[end])
        // - then, this player can take score2_x = remaining_score - opponent_score from the
        // remaining piles
        // 3. thus, given choice x, this player takes score_x = score1_x + score2_x
        // Finally, the max score that this player can take is max(score_x,...)
        if (i == piles.size())
            return 0; // no piles, game over

        if (memo[i][M] != -1)
            return memo[i][M];

        int score = 0;
        for (int x = 1; x <= 2 * M; ++x) {
            if (i + x - 1 >= piles.size())
                break;

            score += piles[i + x - 1]; // takes x piles first, then considier oppenent's strategy
            const auto opponent = dp(i + x, std::max(x, M), memo, suffixSum, piles);
            memo[i][M] = std::max(memo[i][M], score + suffixSum[i + x] - opponent);
        }
        return memo[i][M];
    }
};