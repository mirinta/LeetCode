#include <vector>

/**
 * You have some coins. The i-th coin has a probability prob[i] of facing heads when tossed.
 *
 * Return the probability that the number of coins facing heads equals "target" if you toss every
 * coin exactly once.
 *
 * ! 1 <= prob.length <= 1000
 * ! 0 <= prob[i] <= 1
 * ! 0 <= target <= prob.length
 * ! Answers will be accepted as correct if they are within 10^-5 of the correct answer.
 */

class Solution
{
public:
    double probabilityOfHeads(std::vector<double>& prob, int target)
    {
        return approach2(prob, target);
    }

private:
    // DP with space optimization, TC = O(N*target), SC = O(target)
    double approach2(const std::vector<double>& prob, int target)
    {
        const int n = prob.size();
        std::vector<double> dp(1 + target, 0);
        dp[0] = 1;
        std::vector<double> prev(1 + target);
        for (int i = 1; i <= n; ++i) {
            prev.assign(dp.begin(), dp.end());
            std::fill(dp.begin(), dp.end(), 0);
            const double head = prob[i - 1];
            dp[0] = (1 - head) * prev[0];
            for (int j = 1; j <= std::min(target, i); ++j) {
                dp[j] = head * prev[j - 1] + (1 - head) * prev[j];
            }
        }
        return dp[target];
    }

    // DP, TC = O(N*target), SC = O(N*target)
    double approach1(const std::vector<double>& prob, int target)
    {
        // dp[i][j] = probability of j coins facing heads after tossing coins[0:i)
        // #NOTE# tossing i coins can get at most i heads, i.e., j <= i
        // base cases:
        // dp[0][0] = 1
        // dp[i>0][0] = (1-prob[0]) * ... * (1-prob[i-1])
        // dp[0][j>0] = 0
        const int n = prob.size();
        std::vector<std::vector<double>> dp(n + 1, std::vector<double>(1 + target, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            const double head = prob[i - 1];
            dp[i][0] = (1 - head) * dp[i - 1][0];
            for (int j = 1; j <= std::min(target, i); ++j) {
                dp[i][j] = head * dp[i - 1][j - 1] + (1 - head) * dp[i - 1][j];
            }
        }
        return dp[n][target];
    }
};