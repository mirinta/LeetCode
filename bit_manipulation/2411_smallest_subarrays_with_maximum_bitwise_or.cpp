#include <array>
#include <vector>

/**
 * You are given a 0-indexed array nums of length n, consisting of non-negative integers. For each
 * index i from 0 to n - 1, you must determine the size of the minimum sized non-empty subarray of
 * nums starting at i (inclusive) that has the maximum possible bitwise OR.
 *
 * - In other words, let Bij be the bitwise OR of the subarray nums[i...j]. You need to find the
 * smallest subarray starting at i, such that bitwise OR of this subarray is equal to max(Bik) where
 * i <= k <= n - 1. The bitwise OR of an array is the bitwise OR of all the numbers in it.
 *
 * Return an integer array answer of size n where answer[i] is the length of the minimum sized
 * subarray starting at i with maximum bitwise OR.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! n == nums.length
 * ! 1 <= n <= 10^5
 * ! 0 <= nums[i] <= 10^9
 */

class Solution
{
public:
    std::vector<int> smallestSubarrays(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::array<int, 32> seen{}; // the first occurrence of bits[i] = 1
        std::fill(seen.begin(), seen.end(), -1);
        std::vector<int> result(n);
        for (int i = n - 1; i >= 0; --i) {
            const int j = helper(seen, nums[i], i);
            result[i] = j - i + 1;
        }
        return result;
    }

private:
    int helper(std::array<int, 32>& seen, int val, int index)
    {
        int max = index;
        for (int i = 0; i < 32; ++i) {
            if (val >> i & 1) {
                seen[i] = seen[i] == -1 ? index : std::min(seen[i], index);
            }
            if (seen[i] != -1) {
                max = std::max(max, seen[i]);
            }
        }
        return max;
    }
};