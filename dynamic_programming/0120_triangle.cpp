#include <climits>
#include <vector>

/**
 * Given a triangle array, return the minimum path sum from top to bottom.
 *
 * For each step, you may move to an adjacent number of the row below. More formally, if you are on
 * index i on the current row, you may move to either index i or index i + 1 on the next row.
 */

class Solution
{
public:
    int minimumTotal(std::vector<std::vector<int>>& triangle)
    {
        // approach 1: time O(n^2), space O(n^2)
        // consider the triangle as a nxn matrix:
        // [2 0 0 0]
        // [3 4 0 0]
        // [6 5 7 0]
        // [4 1 8 3]
        // dp[i][j] = min sum from pos(0,0) to pos(i,j)
        // base cases:
        // - dp[i][0] = prefix sum of the first column of triangle
        // - initialize with INT_MAX, if j = i >= 1, there's no path from pos(i-1,j) to pos(i,j)
        // const auto n = triangle.size();
        // std::vector<std::vector<int>> dp(n, std::vector<int>(n, INT_MAX));
        // dp[0][0] = triangle[0][0];
        // for (int i = 1; i < n; ++i) {
        //     dp[i][0] = dp[i - 1][0] + triangle[i][0];
        // }
        // for (int i = 1; i < n; ++i) {
        //     for (int j = 1; j <= i; ++j) {
        //         dp[i][j] = triangle[i][j];
        //         dp[i][j] += std::min(dp[i - 1][j], dp[i - 1][j - 1]);
        //     }
        // }
        // int result = INT_MAX;
        // for (const auto& val : dp[n - 1]) {
        //     result = std::min(result, val);
        // }
        // return result;

        // approach 2: modify triangle in-place
        const auto n = triangle.size();
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (j == 0) {
                    triangle[i][j] += triangle[i - 1][j];
                } else if (j == i) {
                    triangle[i][j] += triangle[i - 1][j - 1];
                } else {
                    triangle[i][j] += std::min(triangle[i - 1][j], triangle[i - 1][j - 1]);
                }
            }
        }
        int result = INT_MAX;
        for (const auto& val : triangle[n - 1]) {
            result = std::min(result, val);
        }
        return result;
    }
};