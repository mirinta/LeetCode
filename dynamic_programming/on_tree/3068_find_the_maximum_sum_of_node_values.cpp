#include <array>
#include <vector>

/**
 * There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 0-indexed 2D
 * integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge
 * between nodes ui and vi in the tree. You are also given a positive integer k, and a 0-indexed
 * array of non-negative integers nums of length n, where nums[i] represents the value of the node
 * numbered i.
 *
 * Bogdan wants the sum of values of tree nodes to be maximum, for which Bogdan can perform the
 * following operation any number of times (including zero) on the tree:
 *
 * - Choose any edge [u, v] connecting the nodes u and v, and update their values as follows:
 *
 *      - nums[u] = nums[u] XOR k
 *
 *      - nums[v] = nums[v] XOR k
 *
 * Return the maximum possible sum of the values Bogdan can achieve by performing the operation any
 * number of times.
 *
 * ! 2 <= n == nums.length <= 2 * 10^4
 * ! 1 <= k <= 10^9
 * ! 0 <= nums[i] <= 10^9
 * ! edges.length == n - 1
 * ! edges[i].length == 2
 * ! 0 <= edges[i][0], edges[i][1] <= n - 1
 * ! The input is generated such that edges represent a valid tree.
 */

class Solution
{
public:
    long long maximumValueSum(std::vector<int>& nums, int k, std::vector<std::vector<int>>& edges)
    {
        return approach2(nums, k, edges);
    }

private:
    // DP with space optimization, TC = O(N), SC = O(1)
    long long approach2(const std::vector<int>& nums, int k,
                        const std::vector<std::vector<int>>& edges)
    {
        const int n = nums.size();
        long long even = nums[0];
        long long odd = nums[0] ^ k;
        for (int i = 1; i < n; ++i) {
            const long long copy = even;
            even = std::max(even + nums[i], odd + (nums[i] ^ k));
            odd = std::max(odd + nums[i], copy + (nums[i] ^ k));
        }
        return even;
    }

    // DP, TC = O(N), SC = O(N)
    long long approach1(const std::vector<int>& nums, int k,
                        const std::vector<std::vector<int>>& edges)
    {
        // Choose edge(u,v), then nums[u]'=nums[u]^k and nums[v]'=nums[v]^k.
        // Choose edge(v,w), then nums[v]''=nums[v]'^k=nums[v], nums[w]'=nums[w]^k.
        // It means if node v and node w are connected,
        // then we can change their values while keeping other nodes' value unchanged.
        // The problem is equivalent to "find the max sum by changing an even num of nodes' values".
        // dp[i][0] = max sum of nums[0:i] by changing an even num of values
        // dp[i][1] = max sum of nums[0:i] by changing an odd num of values
        const int n = nums.size();
        std::vector<std::array<long long, 2>> dp(n, {0, 0});
        dp[0][0] = nums[0];
        dp[0][1] = nums[0] ^ k;
        for (int i = 1; i < n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0] + nums[i], dp[i - 1][1] + (nums[i] ^ k));
            dp[i][1] = std::max(dp[i - 1][1] + nums[i], dp[i - 1][0] + (nums[i] ^ k));
        }
        return dp[n - 1][0];
    }
};