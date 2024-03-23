#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an array nums of positive integers and a positive integer k.
 *
 * A subset of nums is beautiful if it does not contain two integers with an absolute difference
 * equal to k.
 *
 * Return the number of non-empty beautiful subsets of the array nums.
 *
 * A subset of nums is an array that can be obtained by deleting some (possibly none) elements from
 * nums. Two subsets are different if and only if the chosen indices to delete are different.
 *
 * ! 1 <= nums.length <= 20
 * ! 1 <= nums[i], k <= 1000
 */

class Solution
{
public:
    int beautifulSubsets(std::vector<int>& nums, int k) { return approach2(nums, k); }

private:
    // DP, TC = O(NlogN), SC = O(N)
    int approach2(const std::vector<int>& nums, int k)
    {
        // if a-b=k, then a%k = b%k
        // if a%k != b%k, then both a and b can be picked
        // if a%k = b%k and a and b are adjacent integers,
        // then we can't pick them both, i.e., adjacent integers can't be picked
        // thus, we can divide nums into groups according to nums[x]%k
        // within each group, the problem is similar to "House Robber"
        std::unordered_map<int, int> count;
        std::unordered_map<int, std::vector<int>> map; // <nums[x]%k, group of distinct integers>
        for (const auto& val : nums) {
            count[val]++;
        }
        for (const auto& [val, freq] : count) {
            map[val % k].push_back(val);
        }
        int result = 1;
        for (auto& [key, group] : map) {
            std::sort(group.begin(), group.end());
            const int n = group.size();
            std::vector<int> dp(n + 1, 0);
            dp[0] = 1;
            dp[1] = 1 << count[group[0]];
            for (int i = 2; i <= n; ++i) {
                const int curr = group[i - 1];
                const int prev = group[i - 2];
                if (curr - prev == k) {
                    // case 1.1: curr is not picked, then dp[i-1]
                    // case 1.2: curr is picked and prev is not picked, then
                    // dp[i-2]*(2^count[curr]-1)
                    // - count[i] = frequency of curr
                    // - any subset (except empty subset) is valid
                    dp[i] = dp[i - 1] + dp[i - 2] * ((1 << count[curr]) - 1);
                } else {
                    // case 2.1: curr is not picked, then dp[i-1]
                    // case 2.2: curr is picked, then dp[i-1]*(2^count[curr]-1)
                    dp[i] = dp[i - 1] << count[curr];
                }
            }
            result *= dp[n];
        }
        return result - 1; // subtract empty subset
    }

    // Backtracking, TC = O(2^N), SC = O(N)
    int approach1(const std::vector<int>& nums, int k)
    {
        int result = 0;
        std::unordered_map<int, int> map;
        backtrack(result, map, 0, k, nums);
        return result - 1; // subtract empty subset
    }

    void backtrack(int& result, std::unordered_map<int, int>& map, int i, int k,
                   const std::vector<int>& nums)
    {
        if (i == nums.size()) {
            result++;
            return;
        }
        // case 1: nums[i] is not picked
        backtrack(result, map, i + 1, k, nums);
        // case 2: nums[i] is picked iff nums[i]-k and nums[i]+k are not picked
        if (map[nums[i] + k] <= 0 && map[nums[i] - k] <= 0) {
            map[nums[i]]++;
            backtrack(result, map, i + 1, k, nums);
            map[nums[i]]--;
        }
    }
};