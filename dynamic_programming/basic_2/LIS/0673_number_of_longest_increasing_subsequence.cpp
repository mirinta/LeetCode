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
        const int n = nums.size();
        // dp[i] = length of LIS ending at nums[i]
        // X X X X X j X i
        // |<-dp[j]->|
        // |<---dp[i]--->|, if nums[i] > nums[j], dp[i] = 1 + dp[j]
        // count[i] = num of LIS ending at nums[i]
        std::vector<int> dp(n, 1);
        std::vector<int> count(n, 1);
        int lengthOfLIS = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] <= nums[j])
                    continue; // {...,nums[j],nums[i]} is not a strictly increasing subsequence

                if (dp[i] < 1 + dp[j]) {
                    dp[i] = 1 + dp[j];
                    count[i] = count[j];
                } else if (dp[i] == 1 + dp[j]) {
                    count[i] += count[j];
                }
            }
            lengthOfLIS = std::max(lengthOfLIS, dp[i]);
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            if (dp[i] == lengthOfLIS) {
                result += count[i];
            }
        }
        return result;
    }
};