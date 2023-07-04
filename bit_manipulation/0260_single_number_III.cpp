#include <vector>

/**
 * Given an integer array nums, in which exactly two elements appear only once and all the other
 * elements appear exactly twice. Find the two elements that appear only once. You can return the
 * answer in any order.
 *
 * You must write an algorithm that runs in linear runtime complexity and uses only constant extra
 * space.
 *
 * ! 2 <= nums.length <= 3 * 10^4
 * ! -2^31 <= nums[i] <= 2^31 - 1
 * ! Each integer in nums will appear twice, only two integers will appear once.
 */

class Solution
{
public:
    std::vector<int> singleNumber(std::vector<int>& nums)
    {
        // nums = [x,x,y,y,A,B]
        // - if A=B, it contradicts to the problem
        unsigned a_xor_b = 0; // prevent overflow
        for (const auto& val : nums) {
            a_xor_b ^= val;
        }
        // how to split a and b from a^b?
        // since A!=B, then there are at least 1 bit in A that is different from B
        // assume the ith bit is different, then the ith bit of A^B is 1
        unsigned diff = a_xor_b & (-a_xor_b); // remain the last 1 and set all the other bits to 0
        // for any P in nums, P^diff=0 means the ith bit of P is 0
        // - the ith bit of P is either the same as A or the same as B
        // - but it can't be the same as both A and B
        // thus, we can split A and B
        int a = 0;
        int b = 0;
        for (const auto& val : nums) {
            if (diff & val) {
                a ^= val;
            } else {
                b ^= val;
            }
        }
        return {a, b};
    }
};