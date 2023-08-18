#include <algorithm>
#include <vector>

/**
 * Given an array of intervals where intervals[i] = [start_i, end_i], merge all overlapping
 * intervals, and return an array of the non-overlapping intervals that cover all the intervals in
 * the input.
 *
 * ! 1 <= intervals.length <= 10^4
 * ! intervals[i].length == 2
 * ! 0 <= start_i <= end_i <= 10^4
 */

class Solution
{
public:
    // time O(NlogN), space O(std::sort+N)
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals)
    {
        if (intervals.empty())
            return {};

        std::sort(intervals.begin(), intervals.end(),
                  [](const auto& v1, const auto& v2) { return v1[0] < v2[0]; });
        // i0<---->i1
        //     j0<---->j1
        //                 k0<---->k1
        // after merging:
        // i0<-------->j1  k0<---->k1
        const int n = intervals.size();
        std::vector<std::vector<int>> result;
        result.push_back(intervals[0]);
        for (int i = 1; i < n; ++i) {
            if (intervals[i][0] <= result.back()[1]) {
                result.back()[1] = std::max(result.back()[1], intervals[i][1]);
            } else {
                result.push_back(intervals[i]);
            }
        }
        return result;
    }
};