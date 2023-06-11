#include <vector>

/**
 * You are given an integer array "cost" where cost[i] is the cost of ith step on a staircase. Once
 * you pay the cost, you can either climb one for two steps.
 *
 * You can either start from the step with index 0, or the step with index 1.
 *
 * Return the minimum cost to reach the top of the floor.
 *
 * ! cost[i] >= 0
 *
 * Example:
 * Input: cost = [#1#, 100, #1#, 1, #1#, 100, #1#, #1#, 100, #1#]
 * Output: 6
 * Explanation: You will start at index 0.
 * - Pay 1 and climb two steps to reach index 2.
 * - Pay 1 and climb two steps to reach index 4.
 * - Pay 1 and climb two steps to reach index 6.
 * - Pay 1 and climb one step to reach index 7.
 * - Pay 1 and climb two steps to reach index 9.
 * - Pay 1 and climb one step to reach the top.
 * The total cost is 6.
 */

class Solution
{
public:
    int minCostClimbingStairs(std::vector<int>& cost)
    {
        const auto n = cost.size();
        if (n < 2)
            return -1;

        // the start position is unknown (0 or 1), but the destination is known (n-1)
        // so we deduce backwards:
        // dp[i] = min cost to reach the top if we start from the ith stair
        // - we need to pay for the ith stair first
        std::vector<int> dp(n, 0);
        // base cases:
        // - dp[n-1] = cost[n-1], we are standing at the top, just pay for the current stair
        // - dp[n-2] = cost[n-2], pay for the current stair first, and then move 1 step to reach the
        // top
        dp[n - 1] = cost[n - 1];
        dp[n - 2] = cost[n - 2];
        for (int i = n - 3; i >= 0; --i) {
            dp[i] = cost[i] + std::min(dp[i + 1], dp[i + 2]);
        }
        return std::min(dp[0], dp[1]);
    }
};