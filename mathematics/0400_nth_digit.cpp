/**
 * Given an integer n, return the nth digit of the infinite integer sequence [1, 2, 3, 4, 5, 6, 7,
 * 8, 9, 10, 11, ...].
 *
 * ! 1 <= n <= 2^31 - 1
 */

class Solution
{
public:
    int findNthDigit(int n)
    {
        // 1~9,     #digits = 1 * 9 * pow(10,0) = 9
        // 10~99,   #digits = 2 * 9 * pow(10,1) = 180
        // 100~999, #digits = 3 * 9 * pow(10,2) = 2700
        // ...      #digits = k * 9 * pow(10,k-1)
        int k = 1;
        long pow = 1;
        while (n > k * 9 * pow) {
            n -= k * 9 * pow;
            k++;
            pow *= 10;
        }
        // n = 13: 2nd digit (1-indexed, from left to right) of value 11
        // - after the above operations: n = 4, k = 2, pow = 10
        // n = 11: 2nd digit (1-indexed, from left to right) of value 10
        // - after the above operations: n = 2, k = 2, pow = 10
        int value = pow + (n - 1) / k;
        const int index = (n - 1) % k; // 0-indexed, from left to right
        for (int i = 0; i < k - 1 - index; ++i) {
            value /= 10;
        }
        return value % 10;
    }
};