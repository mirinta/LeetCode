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
        const int n = piles.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + piles[i - 1];
        }
        std::vector<std::vector<int>> memo(n, std::vector<int>(n + 1, -1));
        return dfs(memo, 0, n, 1, presum);
    }

private:
    // max score that the 1st action player can get at the end of the game piles[lo:n-1]
    int dfs(std::vector<std::vector<int>>& memo, int lo, int n, int M,
            const std::vector<int>& presum)
    {
        if (lo >= n)
            return 0;

        if (memo[lo][M] != -1)
            return memo[lo][M];

        int result = INT_MIN;
        for (int x = 1; x <= std::min(2 * M, n - lo); ++x) {
            const int score = presum[lo + x] - presum[lo];
            result = std::max(result, score + presum[n] - presum[lo + x] -
                                          dfs(memo, lo + x, n, std::max(M, x), presum));
        }
        return memo[lo][M] = result;
    }
};