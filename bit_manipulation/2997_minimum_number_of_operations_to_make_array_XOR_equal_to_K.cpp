#include <vector>

/**
 * You are given a 0-indexed integer array nums and a positive integer k.
 *
 * You can apply the following operation on the array any number of times:
 *
 * Choose any element of the array and flip a bit in its binary representation. Flipping a bit means
 * changing a 0 to 1 or vice versa. Return the minimum number of operations required to make the
 * bitwise XOR of all elements of the final array equal to k.
 *
 * Note that you can flip leading zero bits in the binary representation of elements. For example,
 * for the number (101)2 you can flip the fourth bit and obtain (1101)2.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^6
 * ! 0 <= k <= 10^6
 */

class Solution
{
public:
    int minOperations(std::vector<int>& nums, int k)
    {
        int XOR = 0;
        for (const auto& val : nums) {
            XOR ^= val;
        }
        int result = 0;
        while (XOR != k) {
            if ((XOR & 1) != (k & 1)) {
                result++;
            }
            XOR >>= 1;
            k >>= 1;
        }
        return result;
    }
};