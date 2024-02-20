#include <array>
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
    bool stoneGame(std::vector<int>& piles) { return approach3(piles); }

private:
    using Matrix = std::vector<std::vector<std::array<int, 2>>>;

    // Math, TC = O(1), SC = O(1)
    bool approach3(const std::vector<int>& piles)
    {
        // The num of piles is an even number.
        // piles: 0, 1, ..., n-1, n-1 is an odd number
        // The 1st action player can always pick the piles he want.
        return true;
    }

    // Bottom-up DP, TC = O(N^2), SC = O(N^2)
    bool approach2(const std::vector<int>& piles)
    {
        // dp[i][j][0] = max num of piles the 1st action player can pick
        // dp[i][j][1] = max num of piles the 2nd action player can pick
        const int n = piles.size();
        Matrix dp(n, std::vector<std::array<int, 2>>(n, {0, 0}));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < n; ++j) {
                if (i > j)
                    continue;

                if (i == j) {
                    dp[i][j] = {piles[i], 0};
                    continue;
                }
                const auto [first1, second1] = dp[i + 1][j];
                const auto [first2, second2] = dp[i][j - 1];
                const int case1 = piles[i] + second1; // pick the left most pile
                const int case2 = piles[j] + second2; // pick the rightmost pile
                if (case1 > case2) {
                    dp[i][j] = {case1, first1};
                } else {
                    dp[i][j] = {case2, first2};
                }
            }
        }
        return dp[0][n - 1][0] > dp[0][n - 1][1];
    }

    // Top-down DP, TC = O(N^2), SC = O(N^2)
    bool approach1(const std::vector<int>& piles)
    {
        const int n = piles.size();
        Matrix memo(n, std::vector<std::array<int, 2>>(n, {-1, -1}));
        const auto [Alice, Bob] = dp(memo, 0, n - 1, piles);
        return Alice > Bob;
    }

    // The game starts with piles[lo:hi].
    // return[0] = max num of piles the 1st action player can pick at the end of the game
    // return[1] = max num of piles the 2nd action player can pick at the end of the game
    std::array<int, 2> dp(Matrix& memo, int lo, int hi, const std::vector<int>& piles)
    {
        if (lo > hi)
            return {0, 0};

        if (memo[lo][hi][0] != -1 && memo[lo][hi][1] != -1)
            return memo[lo][hi];

        // case 1: the 1st action player picks the leftmost pile
        // then he becomes the 2nd action player in the next round
        const auto [first1, second1] = dp(memo, lo + 1, hi, piles);
        const int case1 = piles[lo] + second1;
        // case 2: the 1st action player picks the rightmost pile
        // then he becomes the 2nd action player in the next round
        const auto [first2, second2] = dp(memo, lo, hi - 1, piles);
        const int case2 = piles[hi] + second2;
        if (case1 > case2)
            return memo[lo][hi] = {case1, first1};

        return memo[lo][hi] = {case2, first2};
    }
};