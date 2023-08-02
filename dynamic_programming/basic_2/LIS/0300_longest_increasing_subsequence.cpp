#include <algorithm>
#include <vector>

/**
 * Given an integer array "nums", return the length of the longest strictly increasing subsequence.
 *
 * ! Can you come up with an algorithm that runs in O(nlogn) time complexity?
 *
 * ! 1 <= nums.length <= 2500
 * ! -10^4 <= nums[i] <= 10^4
 *
 * Example:
 * Input: nums = [10, 9, 2, 5, 3, 7, 101, 18]
 * Output: 4
 * Explanation: the longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4.
 */

class Solution
{
public:
    int lengthOfLIS(std::vector<int>& nums) { return approach2(nums); }

private:
    // binary search, time O(nlogn), space O(n)
    int approach2(std::vector<int>& nums)
    {
        const int n = nums.size();
        // maintain vec in strictly increasing order
        std::vector<int> vec;
        for (const auto& val : nums) {
            if (vec.empty() || val > vec.back()) {
                vec.push_back(val);
            } else {
                // find the first index i s.t. vec[i] >= val
                // [X X i i+1 ... X], replace vec[i] with val
                auto iter = std::lower_bound(vec.begin(), vec.end(), val);
                if (iter != vec.end()) {
                    *iter = val;
                }
            }
        }
        return vec.size();
    }

    // DP, time O(n^2), space O(n)
    int approach1(std::vector<int>& nums)
    {
        // dp[i] = length of LIS that ends with nums[i]
        const int n = nums.size();
        std::vector<int> dp(n, 1);
        for (int i = 1; i < n; ++i) {
            // X X j X X i, find a best j to maximize dp[i] = 1 + dp[j]
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] > nums[j]) {
                    dp[i] = std::max(dp[i], 1 + dp[j]);
                }
            }
        }
        return *std::max_element(dp.begin(), dp.end());
    }
};
