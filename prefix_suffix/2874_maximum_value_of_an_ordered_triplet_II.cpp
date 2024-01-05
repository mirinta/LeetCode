#include <vector>

/**
 * You are given a 0-indexed integer array nums.
 *
 * Return the maximum value over all triplets of indices (i, j, k) such that i < j < k. If all such
 * triplets have a negative value, return 0.
 *
 * The value of a triplet of indices (i, j, k) is equal to (nums[i] - nums[j]) * nums[k].
 *
 * ! 3 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^6
 */

class Solution
{
public:
    long long maximumTripletValue(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<long long> prefixMax(n, INT_MIN); // prefixMax[i] = max element in nums[0:i)
        std::vector<long long> suffixMax(n, INT_MIN); // suffixMax[i] = max element in nums[n-1:i)
        for (int i = 1; i < n; ++i) {
            prefixMax[i] = std::max<long long>(prefixMax[i - 1], nums[i - 1]);
            suffixMax[n - i - 1] = std::max<long long>(suffixMax[n - i], nums[n - i]);
        }
        long long result = 0;
        for (int i = 1; i < n - 1; ++i) {
            result = std::max(result, (prefixMax[i] - nums[i]) * suffixMax[i]);
        }
        return result;
    }
};