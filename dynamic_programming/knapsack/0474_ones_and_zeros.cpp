#include <string>
#include <vector>

/**
 * You are given an array of binary strings strs and two integers m and n.
 *
 * Return the size of the largest subset of strs such that there are at most m 0's and n 1's in the
 * subset.
 *
 * A set x is a subset of a set y if all elements of x are also elements of y.
 *
 * ! 1 <= strs.length <= 600
 * ! 1 <= strs[i].length <= 100
 * ! strs[i] consists only of digits '0' and '1'.
 * ! 1 <= m, n <= 100
 */

class Solution
{
public:
    int findMaxForm(const std::vector<std::string>& strs, int m, int n)
    {
        return approach2(strs, m, n);
    }

private:
    using Vector = std::vector<int>;

    int approach1(const std::vector<std::string>& strs, int m, int n)
    {
        if (strs.empty() || m < 0 || n < 0)
            return 0;

        const auto l = strs.size();
        // dp[k][i][j] = size of largest subset of strs[0:k) that has at most i 0's and j 1's
        std::vector<std::vector<Vector>> dp(l + 1, std::vector<Vector>(m + 1, Vector(n + 1, 0)));
        for (int k = 1; k <= l; ++k) {
            const auto& str = strs[k - 1];
            const int zeros = std::count(str.cbegin(), str.cend(), '0');
            const int ones = str.size() - zeros;
            for (int i = 0; i <= m; ++i) {
                for (int j = 0; j <= n; ++j) {
                    if (i - zeros < 0 || j - ones < 0) {
                        dp[k][i][j] = dp[k - 1][i][j];
                    } else {
                        dp[k][i][j] = std::max(dp[k - 1][i][j], 1 + dp[k - 1][i - zeros][j - ones]);
                    }
                }
            }
        }
        return dp[l][m][n];
    }

    int approach2(const std::vector<std::string>& strs, int m, int n)
    {
        if (strs.empty() || m < 0 || n < 0)
            return 0;

        // dp[i][j] = size of largest subset that has at most i 0's and j 1's
        std::vector<Vector> dp(m + 1, Vector(n + 1, 0));
        for (const auto& str : strs) {
            const int zeros = std::count(str.cbegin(), str.cend(), '0');
            const int ones = str.size() - zeros;
            for (int i = m; i >= zeros; --i) {
                for (int j = n; j >= ones; --j) {
                    dp[i][j] = std::max(dp[i][j], 1 + dp[i - zeros][j - ones]);
                }
            }
        }
        return dp[m][n];
    }
};