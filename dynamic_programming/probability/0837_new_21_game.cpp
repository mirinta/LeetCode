#include <vector>

/**
 * Alice plays the following game, loosely based on the card game "21".
 *
 * Alice starts with 0 points and draws numbers while she has less than k points. During each draw,
 * she gains an integer number of points randomly from the range [1, maxPts], where maxPts is an
 * integer. Each draw is independent and the outcomes have equal probabilities.
 *
 * Alice stops drawing numbers when she gets k or more points.
 *
 * Return the probability that Alice has n or fewer points.
 *
 * Answers within 10^-5 of the actual answer are considered accepted.
 *
 * Example:
 * Input: n = 6, k = 1, maxPts = 10
 * Output: 0.60000
 * Explanation: Alice gets a single card, then stops.
 * In 6 out of 10 possibilities, she is at or below 6 points.
 */

class Solution
{
public:
    double new21Game(int n, int k, int maxPts)
    {
        // dp[i] = probability of getting i points, i in [0, n]
        // at the ith round,
        // - choices are j = {1, 2, ..., maxPts}
        // - first, make sure there's enough room for j, i.e., i - j >= 0
        // - second, make sure the termination condition is not satisfied, i.e., i - j < k
        // - for each valid j,
        //   the probability of picking j is 1/maxPts,
        //   and the probability of getting the remaining points is dp[i - j]
        // - thus, dp[i] = dp[i-j_0]/maxPts +...+ dp[i-j_m]/maxPts, where {j_0,...,j_m} are valid
        // j's base case: the game starts from 0 points, so dp[0] = 1 the game stops when points >=
        // k, the probability of points <= n is dp[k]+...+dp[n]
        if (k == 0 || n >= k + maxPts)
            return 1.0;

        std::vector<double> dp(n + 1, 0.0);
        dp[0] = 1.0;
        // for (int i = 1; i <= n; ++i) {
        //     for (int j = 1; j <= maxPts; ++j) {
        //         if (i >= j && i - j < k) {
        //             dp[i] += dp[i - j] / maxPts;
        //         }
        //     }
        // }
        double result = 0.0;
        double sum = 1.0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = sum / maxPts;
            if (i < k) {
                sum += dp[i];
            } else {
                result += dp[i];
            }
            if (i >= maxPts) {
                sum -= dp[i - maxPts];
            }
        }
        return result;
    }
};