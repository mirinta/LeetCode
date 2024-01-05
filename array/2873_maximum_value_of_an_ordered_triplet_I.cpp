#include <vector>

/**
 * You are given a 0-indexed integer array nums.
 *
 * Return the maximum value over all triplets of indices (i, j, k) such that i < j < k. If all such
 * triplets have a negative value, return 0.
 *
 * The value of a triplet of indices (i, j, k) is equal to (nums[i] - nums[j]) * nums[k].
 *
 * ! 3 <= nums.length <= 100
 * ! 1 <= nums[i] <= 10^6
 */

class Solution
{
public:
    long long maximumTripletValue(std::vector<int>& nums)
    {
        const int n = nums.size();
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    result = std::max(result, (nums[i] - nums[j]) * 1LL * nums[k]);
                }
            }
        }
        return result;
    }
};