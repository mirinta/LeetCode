#include <algorithm>
#include <vector>

/**
 * You are given an array of events where events[i] = [startDayi, endDayi, valuei]. The ith event
 * starts at startDayi and ends at endDayi, and if you attend this event, you will receive a value
 * of valuei. You are also given an integer k which represents the maximum number of events you can
 * attend.
 *
 * You can only attend one event at a time. If you choose to attend an event, you must attend the
 * entire event. Note that the end day is inclusive: that is, you cannot attend two events where one
 * of them starts and the other ends on the same day.
 *
 * Return the maximum sum of values that you can receive by attending events.
 *
 * ! 1 <= k <= events.length
 * ! 1 <= k * events.length <= 10^6
 * ! 1 <= startDayi <= endDayi <= 10^9
 * ! 1 <= valuei <= 10^6
 */

class Solution
{
public:
    int maxValue(std::vector<std::vector<int>>& events, int k)
    {
        // sort events by endDay
        std::sort(events.begin(), events.end(),
                  [](const auto& e1, const auto& e2) { return e1[1] < e2[1]; });
        // dp[i][j] = max value within the first i events with at most k chosen events
        // base case: dp[i][0] = 0, for all i
        const int n = events.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, -1));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            // [START...pth...END]
            //                   [START...ith...END]
            // find the last event p (0-indexed) s.t. end_p < start_i
            const int p = find(events[i - 1][0], events);
            for (int j = 1; j <= k; ++j) {
                // case1: choose the ith event
                // - dp[i][j] = dp[i - 1][k];
                // case2: choose the ith event
                // - dp[i][j] = dp[p + 1][k - 1] + value_i
                // - #NOTE# p is 0-indexed
                dp[i][j] = std::max(dp[i - 1][j], dp[p + 1][j - 1] + events[i - 1][2]);
            }
        }
        return *std::max_element(dp[n].begin(), dp[n].end());
    }

private:
    int find(int startDay, const std::vector<std::vector<int>>& events)
    {
        int lo = 0;
        int hi = events.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (events[mid][1] >= startDay) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } // the loop is terminated when lo = hi + 1
        return hi;
    }
};