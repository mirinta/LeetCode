#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an array of intervals, where intervals[i] = [start_i, end_i] and each start_i is
 * unique.
 *
 * The right interval for an interval i is an interval j such that start_j >= end_i and start_j is
 * minimized. Note that i may equal j.
 *
 * Return an array of right interval indices for each interval i. If no right interval exists for
 * interval i, then put -1 at index i.
 *
 * ! 1 <= intervals.length <= 2 * 10^4
 * ! intervals[i].length == 2
 * ! -10^6 <= start_i <= end_i <= 10^6
 * ! The start point of each interval is unique.
 */

class Solution
{
public:
    std::vector<int> findRightInterval(std::vector<std::vector<int>>& intervals)
    {
        if (intervals.empty())
            return {};

        // interval to original index
        // since the start points are unique, we can use them as keys
        std::unordered_map<int, int> map;
        for (int i = 0; i < intervals.size(); ++i) {
            map[intervals[i][0]] = i;
        }
        std::sort(intervals.begin(), intervals.end());
        std::vector<int> result(intervals.size(), 0);
        for (const auto& interval : intervals) {
            const int index = binarySearch(interval[1], intervals);
            result[map[interval[0]]] = index < 0 ? -1 : map[intervals[index][0]];
        }
        return result;
    }

private:
    // find the first interval s.t. interval[0] >= endPoint
    int binarySearch(int endPoint, const std::vector<std::vector<int>>& intervals)
    {
        int lo = 0;
        int hi = intervals.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (intervals[mid][0] < endPoint) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        } // the loop is terminated when lo = hi + 1
        return lo == intervals.size() ? -1 : lo;
    }
};
