#include <vector>

/**
 * 给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），
 * 每段绳子的长度记为 k[0],k[1]...k[m-1] 。
 *
 * 请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？
 *
 * 例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
 *
 * ! 2 <= n <= 58
 *
 * ! 本题与LC 343相同
 */

class Solution
{
public:
    int cuttingRope(int n)
    {
        if (n < 2)
            return 0;

        std::vector<int> dp(n + 1, 0);
        dp[2] = 1; // break into at least 2 parts, dp[0]=dp[1]=0
        for (int i = 1; i <= n; ++i) {
            for (int cut = 1; cut <= i / 2; ++cut) {
                dp[i] = std::max({dp[i], cut * (i - cut), cut * dp[i - cut]});
            }
        }
        return dp[n];
    }
};