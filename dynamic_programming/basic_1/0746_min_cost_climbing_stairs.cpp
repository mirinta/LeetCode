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
    int minCostClimbingStairs(std::vector<int>& cost) { return approach2(cost); }

private:
    int approach2(std::vector<int>& cost)
    {
        // DP with space optimization
        const int n = cost.size();
        int oneStepToTop = cost[n - 1];
        int twoStepsToTop = cost[n - 2];
        for (int i = n - 3; i >= 0; --i) {
            const int temp = std::min(oneStepToTop, twoStepsToTop) + cost[i];
            oneStepToTop = twoStepsToTop;
            twoStepsToTop = temp;
        }
        return std::min(oneStepToTop, twoStepsToTop);
    }

    int approach1(std::vector<int>& cost)
    {
        const int n = cost.size();
        // dp[i] = min cost from staircase i (0-indexed) to n-1
        std::vector<int> dp(n, 0);
        dp[n - 1] = cost[n - 1];
        dp[n - 2] = cost[n - 2];
        for (int i = n - 3; i >= 0; --i) {
            dp[i] = std::min(dp[i + 1], dp[i + 2]) + cost[i];
        }
        return std::min(dp[0], dp[1]);
    }
};