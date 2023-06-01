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
    double probabilityOfHeads(const std::vector<double>& prob, int target)
    {
        const auto n = prob.size();
        // dp[i][j] = prob of j heads tossing coins[0:i)
        // base cases:
        // - dp[0][0] = 1
        // - dp[0][j] = 0, no coins to toss
        // - dp[i][0] = (1-prob_0) * ... * (1-prob_k), where k=i-1
        std::vector<std::vector<double>> dp(n + 1, std::vector<double>(target + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = dp[i - 1][0] * (1 - prob[i - 1]);
            for (int j = 1; j <= std::min(target, i); ++j) {
                dp[i][j] = prob[i - 1] * dp[i - 1][j - 1] + (1 - prob[i - 1]) * dp[i - 1][j];
            }
        }
        return dp[n][target];
    }
};