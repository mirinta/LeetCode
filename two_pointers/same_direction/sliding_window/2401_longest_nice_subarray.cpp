#include <algorithm>
#include <array>
#include <vector>

/**
 * You are given an array nums consisting of positive integers.
 *
 * We call a subarray of nums nice if the bitwise AND of every pair of elements that are in
 * different positions in the subarray is equal to 0.
 *
 * Return the length of the longest nice subarray.
 *
 * A subarray is a contiguous part of an array.
 *
 * Note that subarrays of length 1 are always considered nice.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution
{
public:
    int longestNiceSubarray(std::vector<int>& nums) { return approach2(nums); }

private:
    // bit manipulation, TC = O(N), SC = O(1)
    int approach2(const std::vector<int>& nums)
    {
        // #NOTE# subarrays of length 1 are valid
        const int n = nums.size();
        int AND = 0;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            while ((AND & nums[right]) != 0) {
                AND ^= nums[left];
                left++;
            }
            AND |= nums[right];
            result = std::max(result, right - left + 1);
        }
        return result;
    }

    // naive bit-by-bit, TC = O(N), SC = O(N)
    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::array<int, 32> count{};
        auto predicate = [](const auto& val) { return val == 0 || val == 1; };
        auto maintain = [&count](int val, int sign) {
            for (int i = 0; i < 32; ++i) {
                count[i] += sign * ((val >> i) & 1);
            }
        };
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            maintain(nums[right], 1);
            while (!std::all_of(count.begin(), count.end(), predicate)) {
                maintain(nums[left], -1);
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};