/**
 * Given two integers left and right that represent the range [left, right], return the bitwise AND
 * of all numbers in this range, inclusive.
 *
 * ! 0 <= left <= right <= 2^31 - 1
 */

class Solution
{
public:
    int rangeBitwiseAnd(int left, int right)
    {
        // find common prefix
        // 4 = 0100
        // 5 = 0101
        // 6 = 0110
        // 7 = 0111
        // 4~7, common prefix is 01
        // 6~7, common prefix is 011
        int shift = 0;
        while (left != right) {
            left >>= 1;
            right >>= 1;
            shift++;
        }
        return left << shift;
    }
};
