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
    // space optimization of approach1
    std::vector<int> approach2(std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        std::sort(nums.begin(), nums.end());
        const int n = nums.size();
        // dp[i] = length of largest divisible subset that ends with nums[i]
        std::vector<int> dp(n, 1);
        int largestIndex = 0;
        int largestSize = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] % nums[j] != 0)
                    continue;

                dp[i] = std::max(dp[i], dp[j] + 1);
            }
            if (dp[i] > largestSize) {
                largestSize = dp[i];
                largestIndex = i;
            }
        }
        // reconstruct the largest subset
        std::vector<int> result;
        int prev = nums[largestIndex];
        for (int i = largestIndex, size = largestSize; i >= 0 && size > 0; --i) {
            if (prev % nums[i] == 0 && size == dp[i]) {
                size--;
                result.push_back(nums[i]);
                prev = nums[i];
            }
        }
        return result;
    }

    std::vector<int> approach1(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());
        const auto n = nums.size();
        // dp[i][j] = largest divisible subset that ends with nums[i]
        // X X X i
        std::vector<std::vector<int>> dp(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] % nums[j] != 0)
                    continue;

                if (dp[j].size() > dp[i].size()) {
                    dp[i] = dp[j];
                }
            }
            dp[i].push_back(nums[i]);
        }
        size_t index = 0;
        size_t size = 0;
        for (size_t i = 0; i < n; ++i) {
            if (dp[i].size() > size) {
                index = i;
                size = dp[i].size();
            }
        }
        return dp[index];
    }
};