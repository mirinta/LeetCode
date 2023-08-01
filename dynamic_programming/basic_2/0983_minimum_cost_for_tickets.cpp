#include <unordered_set>
#include <vector>

/**
 * You have planned some train traveling one year in advance. The days of the year in which you will
 * travel are given as an integer array "days". Each day is an integer from 1 to 365.
 *
 * Train tickets are sold in three different ways:
 *
 * - a 1-day pass is sold for costs[0] dollars,
 *
 * - a 7-day pass is sold for costs[1] dollars, and
 *
 * - a 30-day pass is sold for costs[2] dollars.
 *
 * The passes allow that many days of consecutive travel.
 *
 * - For example, if we get a 7-day pass on day 2, then we can travel for 7 days: 2, 3, 4, 5, 6, 7,
 * and 8.
 *
 * Return the minimum number of dollars you need to travel every day in the given list of days.
 *
 * ! 1 <= days.length <= 365
 * ! 1 <= days[i] <= 365
 * ! days is in strictly increasing order.
 * ! costs.length == 3
 * ! 1 <= costs[i] <= 1000
 */

class Solution
{
public:
    int mincostTickets(std::vector<int>& days, std::vector<int>& costs)
    {
        std::unordered_set<int> travel(days.begin(), days.end());
        const int n = days.back();
        // dp[i] = min cost of the first i days
        std::vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            if (!travel.count(i)) {
                dp[i] = dp[i - 1];
                continue;
            }
            dp[i] = std::min(dp[i], dp[std::max(0, i - 1)] + costs[0]);
            dp[i] = std::min(dp[i], dp[std::max(0, i - 7)] + costs[1]);
            dp[i] = std::min(dp[i], dp[std::max(0, i - 30)] + costs[2]);
        }
        return dp[n];
    }
};
