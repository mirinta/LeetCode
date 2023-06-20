/**
 * Given a non-negative integer x, return the square root of x rounded down to the nearest integer.
 * The returned integer should be non-negative as well.
 *
 * You must not use any built-in exponent function or operator.
 *
 * - For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.
 *
 * ! 0 <= num <= 2^31 - 1
 */

class Solution
{
public:
    int mySqrt(int x)
    {
        if (x < 2)
            return x; // the constraint tells us x in [0, INT_MAX]

        int left = 2;
        int right = x / 2;
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            long long square = mid * mid;
            if (square == x) {
                return mid;
            } else if (square > x) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } // the loop terminated when left = right + 1
        return right;
    }
};
