#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given a string s. We want to partition the string into as many parts as possible so that
 * each letter appears in at most one part.
 *
 * Note that the partition is done so that after concatenating all the parts in order, the resultant
 * string should be s.
 *
 * Return a list of integers representing the size of these parts.
 *
 * ! 1 <= s.length <= 500
 * ! s consists of lowercase English letters.
 */

class Solution
{
public:
    std::vector<int> partitionLabels(const std::string& s) { return approach2(s); }

private:
    std::vector<int> approach2(const std::string& s)
    {
        std::unordered_map<char, int> map; // letter to last occurrence index
        for (int i = 0; i < s.size(); ++i) {
            map[s[i]] = i;
        }
        int start = 0;
        int end = 0;
        std::vector<int> result;
        for (int i = 0; i < s.size(); ++i) {
            end = std::max(end, map[s[i]]);
            if (i == end) {
                result.push_back(i - start + 1);
                start = i + 1;
            }
        }
        return result;
    }

    // Merging intervals, time O(NlogN), space O(N)
    std::vector<int> approach1(const std::string& s)
    {
        // smallest index of letter x, largest index of letter x
        using Interval = std::pair<int, int>;
        std::unordered_map<char, Interval> map;
        for (int i = 0; i < s.size(); ++i) {
            if (!map.count(s[i])) {
                map[s[i]].first = i;
                map[s[i]].second = i;
            } else {
                map[s[i]].second = i;
            }
        }
        std::vector<Interval> intervals;
        intervals.reserve(map.size());
        for (const auto& [c, interval] : map) {
            intervals.push_back(interval);
        }
        std::sort(intervals.begin(), intervals.end());
        // merge intervals
        std::vector<Interval> merged;
        for (const auto& interval : intervals) {
            if (merged.empty() || interval.first > merged.back().second) {
                merged.push_back(interval);
            } else {
                merged.back().second = std::max(merged.back().second, interval.second);
            }
        }
        std::vector<int> result(merged.size());
        for (int i = 0; i < result.size(); ++i) {
            result[i] = merged[i].second - merged[i].first + 1;
        }
        return result;
    }
};
