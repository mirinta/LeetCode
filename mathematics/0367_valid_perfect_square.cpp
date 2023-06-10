#include <cstdint>

/**
 * Given a positive integer "num", return "true" if "num" is a perfect square or "false" otherwise.
 *
 * A perfect square is an integer that is the square of an integer. In other words, it is the
 * product of some integer with itself.
 *
 * You must not use any build-in library function, such as "sqrt".
 */

class Solution
{
    // similar to 0069
    bool isPerfectSquare(int num)
    {
        if (num < 0)
            return false;

        if (num == 0 || num == 1)
            return true;

        int64_t left = 1;
        int64_t right = num / 2 + 1;
        while (left <= right) {
            int64_t mid = left + (right - left) / 2;
            const int64_t product = mid * mid;
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