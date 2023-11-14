#include <algorithm>
#include <vector>

/**
 * You are given a 2D integer array intervals where intervals[i] = [lefti, righti] represents the
 * inclusive interval [lefti, righti].
 *
 * You have to divide the intervals into one or more groups such that each interval is in exactly
 * one group, and no two intervals that are in the same group intersect each other.
 *
 * Return the minimum number of groups you need to make.
 *
 * Two intervals intersect if there is at least one common number between them. For example, the
 * intervals [1, 5] and [5, 8] intersect.
 *
 * ! 1 <= intervals.length <= 10^5
 * ! intervals[i].length == 2
 * ! 1 <= lefti <= righti <= 10^6
 */

class Solution
{
public:
    int minGroups(std::vector<std::vector<int>>& intervals)
    {
        std::vector<std::pair<int, int>> stamps;
        stamps.reserve(intervals.size() * 2);
        for (const auto& interval : intervals) {
            stamps.emplace_back(interval[0], 1);
            stamps.emplace_back(interval[1], -1);
        }
        std::sort(stamps.begin(), stamps.end(), [](const auto& p1, const auto& p2) {
            return p1.first == p2.first ? p1.second > p2.second : p1.first < p2.first;
        });
        int result = 0;
        int count = 0;
        for (const auto& [pos, flag] : stamps) {
            count += flag;
            result = std::max(result, count);
        }
        return result;
    }
};
