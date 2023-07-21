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
    int findNumberOfLIS(std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i] = length of LIS that ends with nums[i]
        // count[i] = num of LIS that ends with nums[i]
        std::vector<int> dp(n, 1);
        std::vector<int> count(n, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] >= nums[i])
                    continue;

                // X X j X X i
                // dp[i] = std::max(dp[i], dp[j] + 1)
                if (dp[j] + 1 > dp[i]) {
                    // new list of LIS = add nums[i] to the end of each LIS that ends with nums[j],
                    // length is increased, but count is the same
                    dp[i] = dp[j] + 1;
                    count[i] = count[j];
                } else if (dp[j] + 1 == dp[i]) {
                    // new list of LIS = list of LIS that ends with nums[i] + list of LIS that ends
                    // with nums[j] length is the same, but count is increased
                    count[i] += count[j];
                }
            }
        }
        const int maxLength = *std::max_element(dp.begin(), dp.end());
        int result = 0;
        for (int i = 0; i < n; ++i) {
            if (dp[i] == maxLength) {
                result += count[i];
            }
        }
        return result;
    }
};