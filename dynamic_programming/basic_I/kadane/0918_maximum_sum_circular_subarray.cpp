#include <vector>

/**
 * Given a circular integer array nums of length n, return the maximum possible sum of a non-empty
 * subarray of nums.
 *
 * A circular array means the end of the array connects to the beginning of the array. Formally, the
 * next element of nums[i] is nums[(i + 1) % n] and the previous element of nums[i] is nums[(i - 1 +
 * n) % n].
 *
 * A subarray may only include each element of the fixed buffer nums at most once. Formally, for a
 * subarray nums[i], nums[i + 1], ..., nums[j], there does not exist i <= k1, k2 <= j with k1 % n ==
 * k2 % n.
 *
 * ! n == nums.length
 * ! 1 <= n <= 3 * 10^4
 * ! -3 * 10^4 <= nums[i] <= 3 * 10^4
 */

class Solution
{
public:
    int maxSubarraySumCircular(std::vector<int>& nums)
    {
        // case1: FRONT...[......]...END
        //                |<---->|
        //                max subarray
        //
        // case2: [FRONT...]......[...END]
        //                  |<-->|
        //                  min subarray
        int totalSum = 0;
        int currentMaxSum = 0;
        int maxSubarraySum = INT_MIN;
        int currentMinSum = 0;
        int minSubarraySum = INT_MAX;
        for (const auto& val : nums) {
            totalSum += val;

            currentMaxSum += val;
            maxSubarraySum = std::max(maxSubarraySum, currentMaxSum);
            currentMaxSum = std::max(currentMaxSum, 0);

            currentMinSum += val;
            minSubarraySum = std::min(minSubarraySum, currentMinSum);
            currentMinSum = std::min(currentMinSum, 0);
        }
        if (totalSum == minSubarraySum)
            return maxSubarraySum;

        return std::max(maxSubarraySum, totalSum - minSubarraySum);
    }
};