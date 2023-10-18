#include <vector>

/**
 * You have a convex n-sided polygon where each vertex has an integer value. You are given an
 * integer array values where values[i] is the value of the ith vertex (i.e., clockwise order).
 *
 * You will triangulate the polygon into n - 2 triangles. For each triangle, the value of that
 * triangle is the product of the values of its vertices, and the total score of the triangulation
 * is the sum of these values over all n - 2 triangles in the triangulation.
 *
 * Return the smallest possible total score that you can achieve with some triangulation of the
 * polygon.
 *
 * ! n == values.length
 * ! 3 <= n <= 50
 * ! 1 <= values[i] <= 100
 */

class Solution
{
public:
    int minScoreTriangulation(std::vector<int>& values)
    {
        /**
         * indices are increasing in clockwise order
         *
         *   k  X
         * X      X
         *   i  j
         *
         * dp[i][j] = min score of triangulating the polygon i->...->k->...->j
         * given i and j, for each k in the range [i+1,j-1]:
         * - #NOTE# [i+1,j-1] must have at least one element, i.e., j-i>=2
         * - we have one triangle and two polygons
         * - i-k-j is a triangle with score T = val[i]*val[j]*val[k]
         * - i->...->k is a polygon, min score of solving this subproblem =  dp[i][k]
         * - k->...->j is another polygon, min score of solving this subproblem = dp[k][j]
         * - thus, dp[i][j] = min(T + dp[i][k] + dp[k][j]), where k is in the range [i+1,j-1]
         */
        const int n = values.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, INT_MAX));
        // base case:
        // - if j-i<2, dp[i][j] = 0, because there's no possible k in the range [i+1,j-1]
        // - otherwise, dp[i][j] = INT_MAX
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                if (j - i < 2) {
                    dp[i][j] = 0;
                }
            }
        }
        for (int i = n - 3; i >= 0; --i) {
            for (int j = i + 2; j < n; ++j) {
                for (int k = i + 1; k <= j - 1; ++k) {
                    const auto product = values[i] * values[j] * values[k];
                    dp[i][j] = std::min(dp[i][j], product + dp[i][k] + dp[k][j]);
                }
            }
        }
        return dp[0][n - 1];
    }
};
