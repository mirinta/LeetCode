#include <algorithm>
#include <vector>

/**
 * Given an integer array "nums", return the length of the longest strictly increasing subsequence.
 *
 * ! Can you come up with an algorithm that runs in O(nlogn) time complexity?
 *
 * ! 1 <= nums.length <= 2500
 * ! -10^4 <= nums[i] <= 10^4
 */

class Solution
{
public:
    int lengthOfLIS(std::vector<int>& nums) { return approach2(nums); }

private:
    // Binary search, time O(NlogN), space O(N)
    int approach2(const std::vector<int>& nums)
    {
        std::vector<int> vec; // strictly increasing
        for (const auto& val : nums) {
            if (vec.empty() || val > vec.back()) {
                vec.push_back(val);
                continue;
            }
            // if val <= vec.back(), find the first index i such that vec[i] >= val
            // replace vec[i] with val
            auto iter = std::lower_bound(vec.begin(), vec.end(), val);
            if (iter != vec.end()) {
                *iter = val;
            }
        }
        return vec.size();
    }

    // DP, time O(N^2), space O(N)
    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i] = length of the LIS that ends with nums[i]
        std::vector<int> dp(n, 1);
        for (int i = 1; i < n; ++i) {
            // X X X X X j i
            // |<-dp[j]->|
            // |<--dp[i]-->|
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] > nums[j]) {
                    dp[i] = std::max(dp[i], 1 + dp[j]);
                }
            }
        }
        return dp[n - 1];
    }
};