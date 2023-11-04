/**
 * Given an integer n, return true if it is a power of four. Otherwise, return false.
 *
 * An integer n is a power of four, if there exists an integer x such that n == 4x.
 *
 * ! -2^31 <= n <= 2^31 - 1
 *
 * ! Follow up: Could you solve it without loops/recursion?
 */

class Solution
{
public:
    bool isPowerOfFour(int n) { return approach2(n); }

private:
    // time O(1), space O(1)
    bool approach2(int n)
    {
        //  1 = 0000 0001
        //  4 = 0000 0100
        // 16 = 0001 0000
        // 64 = 0100 0000
        // if n is a power of 4,
        // its binary form has and only has one bit of 1 located at an even index
        if (n <= 0)
            return false;

        if (n & (n - 1))
            return false;

        // enumerate all binary ones at even indicies
        // 0101 ... 0101 0101
        // 0101 0101 = 0x55
        constexpr int kMask = 0x55555555;
        return n & kMask;
    }

    // time O(logN), space O(1)
    bool approach1(int n)
    {
        if (n <= 0)
            return false;

        while (n % 4 == 0) {
            n /= 4;
        }
        return n == 1;
    }
};
