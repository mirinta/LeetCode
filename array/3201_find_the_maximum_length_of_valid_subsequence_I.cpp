#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * A subsequence sub of nums with length x is called valid if it satisfies:
 *
 * - (sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.
 *
 * Return the length of the longest valid subsequence of nums.
 *
 * A subsequence is an array that can be derived from another array by deleting some or no elements
 * without changing the order of the remaining elements.
 *
 * ! 2 <= nums.length <= 2 * 10^5
 * ! 1 <= nums[i] <= 10^7
 */

class Solution
{
public:
    int maximumLength(std::vector<int>& nums)
    {
        // case 1: same parity, either {odd, odd, ...} or {even, even, ...}
        // case 2: alternating parity, either {odd, even, ...} or {even, odd, ...}
        int odd = 0;
        int even = 0;
        int alter1 = 0;
        int alter2 = 0;
        bool prev1 = 1 - nums[0] % 2;
        bool prev2 = nums[0] % 2;
        for (const auto& val : nums) {
            const bool isOdd = val % 2;
            if (isOdd) {
                odd++;
            } else {
                even++;
            }
            if (isOdd ^ prev1) {
                alter1++;
                prev1 = isOdd;
            }
            if (isOdd ^ prev2) {
                alter2++;
                prev2 = isOdd;
            }
        }
        return std::max({odd, even, alter1, alter2});
    }
};
