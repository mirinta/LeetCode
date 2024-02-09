#include <algorithm>
#include <vector>

/**
 * Given a set of distinct positive integers "nums", return the largest subset answer such that
 * every pair (answer[i], answer[j]) of elements in this subset satisfies:
 *
 * - answer[i] % answer[j] == 0, or
 *
 * - answer[i] % answer[i] == 0
 *
 * If there are multiple solutions, return any of them.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 2 * 10^9
 * ! All the integers in nums are unique.
 */

class Solution
{
public:
    std::vector<int> largestDivisibleSubset(std::vector<int>& nums) { return approach2(nums); }

private:
    // DP with space optimization, TC = O(N^2), SC = O(N)
    std::vector<int> approach2(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        // dp[i] = length of the largest valid subset of nums[0:i] ending at nums[i]
        std::vector<int> dp(n, 1); // single element is a valid subset
        int maxLength = 0;
        int maxIndex = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] % nums[j] != 0)
                    continue;

                dp[i] = std::max(dp[i], 1 + dp[j]);
            }
            if (dp[i] > maxLength) {
                maxLength = dp[i];
                maxIndex = i;
            }
        }
        // reconstruct the result (in any order)
        std::vector<int> result;
        result.reserve(maxLength);
        for (int i = maxIndex, len = maxLength; i >= 0; --i) {
            if (result.empty() || (dp[i] == len && result.back() % nums[i] == 0)) {
                result.push_back(nums[i]);
                len--;
            }
        }
        return result;
    }
    // DP, TC = O(N^2), SC = O(N^2)
    std::vector<int> approach1(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        // dp[i] = largest valid subset of nums[0:i] ending at nums[i]
        // #NOTE# subset with single element is valid
        std::vector<std::vector<int>> dp(n);
        int maxIndex = 0;
        int maxLength = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] % nums[j] != 0)
                    continue;

                if (dp[j].size() > dp[i].size()) {
                    dp[i] = dp[j];
                }
            }
            dp[i].push_back(nums[i]);
            if (dp[i].size() > maxLength) {
                maxLength = dp[i].size();
                maxIndex = i;
            }
        }
        return dp[maxIndex];
    }
};