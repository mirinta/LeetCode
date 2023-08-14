#include <algorithm>
#include <climits>
#include <vector>

/**
 * Given a triangle array, return the minimum path sum from top to bottom.
 *
 * For each step, you may move to an adjacent number of the row below. More formally, if you are on
 * index i on the current row, you may move to either index i or index i + 1 on the next row.
 *
 * ! 1 <= triangle.length <= 200
 * ! triangle[0].length == 1
 * ! triangle[i].length == triangle[i - 1].length + 1
 * ! -10^4 <= triangle[i][j] <= 10^4
 *
 * ! Follow up: Could you do this using only O(n) extra space, where n is the total number of rows
 * ! in the triangle?
 */

class Solution
{
public:
    int minimumTotal(std::vector<std::vector<int>>& triangle) { return approach2(triangle); }

private:
    // 1D-DP, time O(N^2), space O(N)
    int approach2(const std::vector<std::vector<int>>& triangle)
    {
        const int n = triangle.size();
        std::vector<int> dp(n, INT_MAX);
        std::vector<int> iMinus1(n, INT_MAX);
        iMinus1[0] = triangle[0][0];
        for (int i = 1; i < n; ++i) {
            dp[0] = triangle[i][0] + iMinus1[0];
            for (int j = 1; j <= i; ++j) {
                dp[j] = triangle[i][j] + std::min(iMinus1[j], iMinus1[j - 1]);
            }
            std::swap(iMinus1, dp);
        }
        return *std::min_element(iMinus1.begin(), iMinus1.end());
    }

    // 2D-DP, time O(N^2), space O(N^2)
    int approach1(const std::vector<std::vector<int>>& triangle)
    {
        const int n = triangle.size();
        // dp[i][j] = min sum from (0,0) to (i,j)
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, INT_MAX));
        // base cases:
        // - dp[0][j] = triangle[0][j]
        // - dp[i][0] = sum(triangle[0][0]...triangle[i][0])
        dp[0][0] = triangle[0][0];
        for (int i = 1; i < n; ++i) {
            dp[i][0] = triangle[i][0] + dp[i - 1][0];
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= i; ++j) {
                dp[i][j] = triangle[i][j] + std::min(dp[i - 1][j], dp[i - 1][j - 1]);
            }
        }
        return *std::min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};