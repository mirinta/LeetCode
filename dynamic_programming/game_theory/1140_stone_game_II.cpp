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
    int stoneGameII(std::vector<int>& piles)
    {
        // Given a game piles[lo:hi],
        // let A = max num of piles the 1st action player finally get
        // and B = max num of piles the 2nd action player finally get
        // This is a zero-sum game, then A+B = sum of piles[lo:hi]
        const int n = piles.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + piles[i - 1];
        }
        // hi is always n-1 and the max value of M is N
        std::vector<std::vector<int>> memo(n, std::vector<int>(n + 1, -1));
        return dp(memo, 0, n, 1, presum);
    }

private:
    // Given a game piles[lo:n-1],
    // return the max num of piles the 1st action player finally get
    int dp(std::vector<std::vector<int>>& memo, int lo, int n, int M,
           const std::vector<int>& presum)
    {
        if (lo >= n)
            return 0;

        if (memo[lo][M] != -1)
            return memo[lo][M];

        int result = 0;
        for (int x = 1; x <= std::min(2 * M, n - lo); ++x) {
            // The 1st action player picks piles[lo:lo+x-1].
            int score = presum[lo + x] - presum[lo];
            // He becomes the 2nd action player in the next game, i.e., piles[lo+x:n-1].
            score += presum[n] - presum[lo + x] - dp(memo, lo + x, n, std::max(M, x), presum);
            result = std::max(result, score);
        }
        return memo[lo][M] = result;
    }
};