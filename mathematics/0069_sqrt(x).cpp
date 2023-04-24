
/**
 * Given a non-negative integer "x", return the square root of "x" rounded down to the nearest
 * integer. The returned integer should be non-negative as well.
 *
 * You must not use any built-in exponent function or operator.
 */

class Solution
{
public:
    int mySqrt(int x)
    {
        if (x == 0 || x == 1)
            return x;

        int left = 1;
        int right = x / 2 + 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (mid == x / mid)
                return mid;

            if (mid > x / mid) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } // the loop terminated when left = right + 1
        return right;
    }
};