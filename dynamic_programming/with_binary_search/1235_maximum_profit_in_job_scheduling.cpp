#include <algorithm>
#include <unordered_map>
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
        const int n = startTime.size();
        std::vector<std::vector<int>> jobs(n, std::vector<int>(3, 0)); // <start, end, profit>
        for (int i = 0; i < n; ++i) {
            jobs[i][0] = startTime[i];
            jobs[i][1] = endTime[i];
            jobs[i][2] = profit[i];
        }
        // sort by ending times
        std::sort(jobs.begin(), jobs.end(),
                  [](const auto& v1, const auto& v2) { return v1[1] < v2[1]; });
        // dp[i] = max profit at the end of i_end, i represents the ith job
        // #NOTE# jobs are sorted by ending times in ascending order
        // X---j_end
        //   X------X
        //        i_start----i_end
        int result = 0;
        std::unordered_map<int, int> dp;
        for (int i = 0; i < n; ++i) {
            // choice 1: we don't choose jobs[i], dp[i] = dp[i-1]
            // choice 2: choose jobs[i]
            // - find the last j such that j_end <= i_start
            // - if j is found, dp[i] = max(dp[i-1], dp[j] + profit[i])
            // - if j is not found, dp[i] = max(dp[i-1], profit[i])
            int lo = 0;
            int hi = i;
            while (lo <= hi) {
                const int mid = lo + (hi - lo) / 2;
                if (jobs[mid][1] <= jobs[i][0]) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            if (hi < 0) {
                dp[i] = std::max(dp[i - 1], jobs[i][2]);
            } else {
                dp[i] = std::max(dp[i - 1], dp[hi] + jobs[i][2]);
            }
            result = std::max(dp[i], result);
        }
        return result;
    }
};