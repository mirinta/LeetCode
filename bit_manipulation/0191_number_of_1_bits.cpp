#include <stdint.h>

/**
 * Write a function that takes the binary representation of an unsigned integer and returns the
 * number of '1' bits it has (also known as the Hamming weight).
 *
 * Note:
 *
 * - Note that in some languages, such as Java, there is no unsigned integer type. In this case, the
 * input will be given as a signed integer type. It should not affect your implementation, as the
 * integer's internal binary representation is the same, whether it is signed or unsigned.
 *
 * - In Java, the compiler represents the signed integers using 2's complement notation. Therefore,
 * in Example 3, the input represents the signed integer, -3.
 *
 * Example 3:
 * Input: n = 11111111111111111111111111111101
 * Output: 31
 * Explanation:
 * The input binary string 11111111111111111111111111111101 has a total of thirty one '1' bits.
 */

class Solution
{
public:
    int hammingWeight(uint32_t n) { return approach2(n); }

private:
    // Approach1: O(logn)
    int approach1(uint32_t n)
    {
        int count = 0;
        while (n) {
            if (n & 1) {
                count++;
            }
            n >>= 1;
        }
        return count;
    }

    // Approach2: O(m), m is the number of '1' bits of n
    int approach2(uint32_t n)
    {
        int count = 0;
        while (n) {
            count++;
            n = n & (n - 1); // eliminate the last '1'
        }
        return count;
    }
};