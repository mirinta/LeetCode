#include <numeric>
#include <vector>

/**
 * You are installing a billboard and want it to have the largest height. The billboard will have
 * two steel supports, one on each side. Each steel support must be an equal height.
 *
 * You are given a collection of rods that can be welded together. For example, if you have rods of
 * lengths 1, 2, and 3, you can weld them together to make a support of length 6.
 *
 * Return the largest possible height of your billboard installation. If you cannot support the
 * billboard, return 0.
 *
 * ! 1 <= rods.length <= 20
 * ! 1 <= rods[i] <= 1000
 * ! sum(rods[i]) <= 5000
 */

class Solution
{
public:
    int tallestBillboard(const std::vector<int>& rods)
    {
        const int n = rods.size();
        // dp[i][j] = max height of the shorter pile we can achieve using rods[0:i) while
        // the height difference between the shorter and the taller pile is j
        const int maxDiff = std::accumulate(rods.cbegin(), rods.cend(), 0);
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(maxDiff + 1, -1));
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            const int h = rods[i - 1]; // current rod
            for (int j = 0; j <= maxDiff - h; ++j) {
                if (dp[i - 1][j] < 0)
                    continue;

                // option 1: not used
                dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
                // option 2: put it on the taller pile
                dp[i][j + h] = std::max(dp[i][j + h], dp[i - 1][j]);
                // option 3: put it on the shorter pile
                const int diff = std::abs(j - h);
                dp[i][diff] = std::max(dp[i][diff], dp[i - 1][j] + std::min(h, j));
            }
        }
        return dp[n][0];
    }
};