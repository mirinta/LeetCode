#include <algorithm>
#include <vector>

/**
 * Given an integer array "nums", return the number of longest increasing subsequences.
 *
 * Notice that the sequence has to be strictly increasing.
 *
 * ! 1 <= nums.length <= 2000
 * ! -10^6 <= nums[i] <= 10^6
 */

class Solution
{
public:
    int findNumberOfLIS(const std::vector<int>& nums)
    {
        const auto n = nums.size();
        if (n <= 1)
            return n;

        // dp[i] = length of the LIS that ends with nums[i]
        // count[i] = num of the longest LIS that ends with nums[i]
        std::vector<int> dp(n, 1);
        std::vector<int> count(n, 1);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (nums[j] >= nums[i])
                    continue;

                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    count[i] = count[j];
                } else if (dp[j] + 1 == dp[i]) {
                    count[i] += count[j];
                }
            }
        }
        const int maxLength = *std::max_element(dp.cbegin(), dp.cend());
        int result = 0;
        for (size_t i = 0; i < n; ++i) {
            if (dp[i] == maxLength) {
                result += count[i];
            }
        }
        return result;
    }
};