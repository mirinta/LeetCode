/**
 * Given a non-negative integer "x", return the square root of "x" rounded down to the nearest
 * integer. The returned integer should be non-negative as well.
 *
 * You must not use any built-in exponent function or operator.
 *
 * ! 1 <= num <= 2^31 - 1
 */

class Solution
{
public:
    bool isPerfectSquare(int num)
    {
        if (num < 2)
            return true; // the constraint tells us 1 <= num <= INT_MAX

        long long left = 2;
        long long right = num / 2;
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            const long long product = mid * mid;
            if (product == num)
                return true;

            if (product > num) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } // the loop is terminated when mid = right = left - 1
        return false;
    }
};
