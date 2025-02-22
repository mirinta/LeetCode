#include <numeric>
#include <vector>

/**
 * You are given a 0-indexed integer array nums of length n.
 *
 * nums contains a valid split at index i if the following are true:
 *
 * - The sum of the first i + 1 elements is greater than or equal to the sum of the last n - i - 1
 * elements.
 *
 * - There is at least one element to the right of i. That is, 0 <= i < n - 1. Return the
 * number of valid splits in nums.
 *
 * ! 2 <= nums.length <= 10^5
 * ! -10^5 <= nums[i] <= 10^5
 */

class Solution
{
public:
    int waysToSplitArray(std::vector<int>& nums)
    {
        const long long n = nums.size();
        const long long total = std::accumulate(nums.begin(), nums.end(), 0LL);
        int result = 0;
        for (long long i = 0, sum = 0; i < n - 1; ++i) {
            sum += nums[i];
            result += sum >= total - sum;
        }
        return result;
    }
};
