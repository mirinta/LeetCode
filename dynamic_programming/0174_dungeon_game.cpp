#include <vector>

/**
 * The demons had captured the princess and imprisoned her in the bottom-right corner of a
 * "dungeon". The "dungeon" consists of "m x n" rooms laid out in a 2D grid. Our valiant knight was
 * initially positioned in the top-left room and must fight his way through "dungeon" to rescue the
 * princess.
 *
 * The knight has an initial health point represented by a positive integer. If at any point his
 * health point drops to 0 or below, he dies immediately.
 *
 * Some of the rooms are guarded by demons (represented by negative integers), so the knight loses
 * health upon entering these rooms; other rooms are either empty (represented as 0) or contain
 * magic orbs that increase the knight's health (represented by positive integers).
 *
 * To reach the princess as quickly as possible, the knight decides to move only rightward or
 * downward in each step.
 *
 * Return the knight's minimum initial health  so that he can rescue the princess.
 *
 * Note that any room can contain threats or power-ups, even the first root the knight enters and
 * the bottom-right room where the princess is imprisoned.
 */

class Solution
{
public:
    int calculateMinimumHP(std::vector<std::vector<int>>& dungeon)
    {
        // approach 1: DP (iterative)
        const auto m = dungeon.size();
        const auto n = dungeon[0].size();
        // dp[i][j] = min initial HP moving from point(i,j) to point(n-1,n-1)
        // since the knight can only move rightward or downward,
        // d[i][j] is dependent on dp[i+1][j] and dp[i][j+1]
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        // base cases:
        // - dp[m-1][n-1], at the bottom-right
        // - for any i != m-1, dp[i][n-1], points in the last column
        // - for any j != n-1, dp[m-1][j], points in the last row
        dp[m - 1][n - 1] = std::max(1 - dungeon[m - 1][n - 1], 1);
        for (int i = m - 2; i >= 0; --i) {
            dp[i][n - 1] = std::max(dp[i + 1][n - 1] - dungeon[i][n - 1], 1);
        }
        for (int j = n - 2; j >= 0; --j) {
            dp[m - 1][j] = std::max(dp[m - 1][j + 1] - dungeon[m - 1][j], 1);
        }
        for (int i = m - 2; i >= 0; --i) {
            for (int j = n - 2; j >= 0; --j) {
                dp[i][j] = std::max(std::min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j], 1);
            }
        }
        return dp[0][0];
    }

private:
    // approach 2: DP (recursion + memo)
    int calculateMinimumHP_v2(const std::vector<std::vector<int>>& dungeon)
    {
        const auto m = dungeon.size();
        const auto n = dungeon[0].size();
        std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1)); // -1 means not calculated
        return dp(memo, 0, 0, dungeon);
    }
    int dp(std::vector<std::vector<int>>& memo, int i, int j,
           const std::vector<std::vector<int>>& dungeon)
    {
        const auto m = dungeon.size();
        const auto n = dungeon[0].size();
        if (i == m || j == n)
            return INT_MAX;

        if (i == m - 1 && j == n - 1)
            return std::max(1 - dungeon[i][j], 1);

        if (memo[i][j] != -1)
            return memo[i][j];

        const auto hp =
            std::min(dp(memo, i + 1, j, dungeon), dp(memo, i, j + 1, dungeon)) - dungeon[i][j];
        memo[i][j] = std::max(hp, 1);
        return memo[i][j];
    }
};