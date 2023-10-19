#include <vector>

/**
 * There are n piles of stones arranged in a row. The ith pile has stones[i] stones.
 *
 * A move consists of merging exactly k consecutive piles into one pile, and the cost of this move
 * is equal to the total number of stones in these k piles.
 *
 * Return the minimum cost to merge all piles of stones into one pile. If it is impossible, return
 * -1.
 *
 * ! n == stones.length
 * ! 1 <= n <= 30
 * ! 1 <= stones[i] <= 100
 * ! 2 <= k <= 30
 */

class Solution
{
public:
    int mergeStones(std::vector<int>& stones, int k)
    {
        // each time we merge k piles into 1 pile,
        // the total num of piles decreases by k-1
        // assume we have N piles at the beginning,
        // and we finally can merge them into 1 pile
        // then, the total decrement is N-1
        // thus, the problem is solvable if and only if (N-1) % (k-1) == 0
        const int n = stones.size();
        if ((n - 1) % (k - 1) != 0)
            return -1;

        std::vector<int> sum(1 + n, 0); // sum[i] = sum of stones[0:i-1]
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + stones[i - 1];
        }
        // dp[i][j][p] = min cost to merge stones[i:j] into p piles
        // i X X X X X X X X X X q q+1 X X X X X X X X X X X j
        // |<-merge into 1 pile->| |<--merge into p-1 piles->|
        // |<----dp[i][q][1]---->| |<----dp[q+1][j][p-1]---->|
        // |<---------------merge into p piles-------------->|
        // then, merge these p piles into 1 pile
        std::vector<std::vector<std::vector<int>>> dp(
            n, std::vector<std::vector<int>>(n, std::vector<int>(1 + k, INT_MAX)));
        for (int i = 0; i < n; ++i) {
            dp[i][i][1] = 0;
        }
        for (int length = 2; length <= n; ++length) {
            for (int i = 0; i + length - 1 < n; ++i) {
                const int j = i + length - 1;
                for (int p = 2; p <= k; ++p) {
                    if (p > length)
                        continue;

                    for (int q = i; q < j; ++q) {
                        if (dp[i][q][1] == INT_MAX || dp[q + 1][j][p - 1] == INT_MAX)
                            continue;

                        dp[i][j][p] = std::min(dp[i][j][p], dp[i][q][1] + dp[q + 1][j][p - 1]);
                    }
                }
                if (dp[i][j][k] != INT_MAX) {
                    dp[i][j][1] = dp[i][j][k] + sum[j + 1] - sum[i];
                }
            }
        }
        return dp[0][n - 1][1];
    }
};
