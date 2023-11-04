#include <climits>

/**
 * Implement pow(x, n) which calculates x raised to the power n (i.e., x^n)
 *
 * ! -2^31 <= n <= 2^31 - 1
 * ! n is an integer
 * ! Either x is not zero or n > 0.
 */

class Solution
{
public:
    double myPow(double x, int n)
    {
        if (n == 0)
            return 1;

        if (x == 0)
            return 0;

        // -INT_MIN = INT_MAX + 1
        if (n == INT_MIN)
            return myPow(1 / x, INT_MAX) / x;

        if (n < 0)
            return myPow(1 / x, -n);

        if (n % 2 != 0)
            return myPow(x, n - 1) * x;

        const double half = myPow(x, n / 2);
        return half * half;
    }
};
