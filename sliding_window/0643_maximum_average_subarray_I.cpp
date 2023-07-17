#include <vector>

/**
 * You are given an integer array nums consisting of n elements, and an integer k.
 *
 * Find a contiguous subarray whose length is equal to k that has the maximum average value and
 * return this value. Any answer with a calculation error less than 10^-5 will be accepted.
 *
 * ! n == nums.length
 * ! 1 <= k <= n <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 */

class Solution
{
public:
    double findMaxAverage(std::vector<int>& nums, int k)
    {
        double sum = 0;
        for (int i = 0; i < k; ++i) {
            sum += nums[i];
        }
        double maxSum = sum;
        for (int i = k; i < nums.size(); ++i) {
            sum -= nums[i - k];
            sum += nums[i];
            maxSum = std::max(maxSum, sum);
        }
        return maxSum / k;
    }
};