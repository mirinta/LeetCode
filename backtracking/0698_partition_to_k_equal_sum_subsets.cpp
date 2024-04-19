#include <numeric>
#include <vector>

/**
 * Given an integer array nums and an integer k, return true if it is possible to divide this array
 * into k non-empty subsets whose sums are all equal.
 *
 * ! 1 <= k <= nums.length <= 16
 * ! 1 <= nums[i] <= 10^4
 * ! The frequency of each element is in the range [1, 4].
 */

class Solution
{
public:
    bool canPartitionKSubsets(std::vector<int>& nums, int k)
    {
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total % k != 0)
            return false;

        const int target = total / k;
        std::vector<int> sum(k, 0);
        return backtrack(sum, 0, k, target, nums);
    }

private:
    bool backtrack(std::vector<int>& sum, int i, int k, int target, const std::vector<int>& nums)
    {
        if (i == nums.size())
            return true;

        for (int j = 0; j < k; ++j) {
            if (j > 0 && sum[j] == sum[j - 1])
                continue; // adding nums[i] to sum[j-1] is negative

            if (nums[i] + sum[j] > target)
                continue;

            sum[j] += nums[i];
            if (backtrack(sum, i + 1, k, target, nums))
                return true;

            sum[j] -= nums[i];
        }
        return false;
    }
};