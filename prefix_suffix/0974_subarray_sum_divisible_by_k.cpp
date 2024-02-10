#include <vector>

/**
 * Given an integer array nums and an integer k, return the number of non-empty subarrays that have
 * a sum divisible by k.
 *
 * A subarray is a contiguous part of an array.
 *
 * ! 1 <= nums.length <= 3 * 10^4
 * ! -10^4 <= nums[i] <= 10^4
 * ! 2 <= k <= 10^4
 */

class Solution
{
public:
    int subarraysDivByK(std::vector<int>& nums, int k)
    {
        // let presum[i] = sum of nums[0:i-1]
        // sum of nums[j:i] = presum[i+1] - presum[j]
        // we want (presum[i+1] - presum[j]) % k = 0
        // thus, presum[i+1] % k = presum[j] % k
        const int n = nums.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        std::vector<int> freq(k, 0);
        freq[0] = 1;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            int target = presum[i + 1] % k;
            if (target < 0) {
                target += k; // prevent negative values
            }
            result += freq[target];
            freq[target]++;
        }
        return result;
    }
};