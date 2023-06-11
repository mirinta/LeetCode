#include <utility>

/**
 * The Tribonacci sequence Tn is defined as follows:
 *
 * T0 = 0, T1 = 1, T2 = 1, and T(n+3) = T(n) + T(n+1) + T(n+2) for n >= 0.
 *
 * Given "n", return the value of T(n).
 */

class Solution
{
public:
    int tribonacci(int n)
    {
        if (n < 3)
            return n == 0 ? 0 : 1;

        // n starts from 3
        int t_3 = 0; // T(n-3)
        int t_2 = 1; // T(n-2)
        int t_1 = 1; // T(n-1)
        for (int i = 3; i <= n; ++i) {
            // this round:
            // T(n) = T(n-3) + T(n-2) + T(n-1)
            // prepare for the next round:
            // T(n+1) = T(n-2) + T(n-1) + T(n)
            std::swap(t_3, t_2);
            std::swap(t_2, t_1);
            t_1 += t_2 + t_3;
        }
        return t_1;
    }
};