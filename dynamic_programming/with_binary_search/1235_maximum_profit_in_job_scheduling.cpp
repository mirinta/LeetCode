#include <algorithm>
#include <array>
#include <vector>

/**
 * We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i],
 * obtaining a profit of profit[i].
 *
 * You're given the startTime, endTime and profit arrays, return the maximum profit you can take
 * such that there are no two jobs in the subset with overlapping time range.
 *
 * If you choose a job that ends at time X you will be able to start another job that starts at time
 * X.
 *
 * ! 1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
 * ! 1 <= startTime[i] < endTime[i] <= 10^9
 * ! 1 <= profit[i] <= 10^4
 */

class Solution
{
public:
    int jobScheduling(std::vector<int>& startTime, std::vector<int>& endTime,
                      std::vector<int>& profit)
    {
        const int n = profit.size();
        std::vector<std::array<int, 3>> jobs(n); // <start, end, profit>
        for (int i = 0; i < n; ++i) {
            jobs[i][0] = startTime[i];
            jobs[i][1] = endTime[i];
            jobs[i][2] = profit[i];
        }
        // sort jobs by ending time
        std::sort(jobs.begin(), jobs.end(),
                  [](const auto& job1, const auto& job2) { return job1[1] < job2[1]; });
        // dp[i] = max profit of scheduling jobs[0:i]
        std::vector<int> dp(n, INT_MIN);
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            const auto& [start, end, gain] = jobs[i];
            dp[i] = i > 0 ? std::max(dp[i - 1], gain) : gain;
            // find the largest j such that jobs[j].end <= jobs[i].start
            auto iter = std::upper_bound(jobs.begin(), jobs.end(), start,
                                         [](int time, const auto& job) { return job[1] > time; });
            if (iter != jobs.begin()) {
                dp[i] = std::max(dp[i], dp[std::prev(iter) - jobs.begin()] + gain);
            }
            result = std::max(result, dp[i]);
        }
        return result;
    }
};