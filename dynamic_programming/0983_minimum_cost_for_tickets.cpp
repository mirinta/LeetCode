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
    int mincostTickets(const std::vector<int>& days, const std::vector<int>& costs)
    {
        const std::vector<int> durations{1, 7, 30};
        std::vector<int> memo(days.size(), -1);
        return dp(0, memo, durations, days, costs);
    }

private:
    // dp(start,...) = min cost of traveling in days[start:n)
    int dp(int start, std::vector<int>& memo, const std::vector<int>& durations,
           const std::vector<int>& days, const std::vector<int>& costs)
    {
        if (start >= days.size())
            return 0;

        if (memo[start] != -1)
            return memo[start];

        int minCost = INT_MAX;
        for (int choice = 0; choice < 3; ++choice) {
            const auto expireDay = days[start] + durations[choice];
            int k = start;
            while (k < days.size() && days[k] < expireDay) {
                k++;
            }
            minCost = std::min(minCost, costs[choice] + dp(k, memo, durations, days, costs));
        }
        memo[start] = minCost;
        return minCost;
    }
};