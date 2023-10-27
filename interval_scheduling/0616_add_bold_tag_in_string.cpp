#include <algorithm>
#include <string>
#include <vector>

/**
 * You are given a string s and an array of strings words.
 *
 * You should add a closed pair of bold tag <b> and </b> to wrap the substrings in s that exist in
 * words.
 *
 * - If two such substrings overlap, you should wrap them together with only one pair of closed
 * bold-tag.
 *
 * - If two substrings wrapped by bold tags are consecutive, you should combine them.
 *
 * Return s after adding the bold tags.
 *
 * ! 1 <= s.length <= 1000
 * ! 0 <= words.length <= 100
 * ! 1 <= words[i].length <= 1000
 * ! s and words[i] consist of English letters and digits.
 * ! All the values of words are unique.
 *
 * ! This question is the same as 758.
 */

class Solution
{
public:
    std::string addBoldTag(std::string s, std::vector<std::string>& words)
    {
        std::vector<std::pair<int, int>> intervals;
        for (const auto& word : words) {
            int start = s.find(word);
            while (start != std::string::npos) {
                intervals.emplace_back(start, start + word.size() - 1);
                start = s.find(word, start + 1);
            }
        }
        mergeIntervals(intervals);
        int count = 0;
        for (const auto& [i, j] : intervals) {
            s.insert(i + count, kBoldTagBegin);
            count += kBoldTagBegin.size();
            s.insert(j + 1 + count, kBoldTagEnd);
            count += kBoldTagEnd.size();
        }
        return s;
    }

private:
    const std::string kBoldTagBegin{"<b>"};
    const std::string kBoldTagEnd{"</b>"};

    void mergeIntervals(std::vector<std::pair<int, int>>& intervals)
    {
        if (intervals.empty() || intervals.size() == 1)
            return;

        std::sort(intervals.begin(), intervals.end());
        std::vector<std::pair<int, int>> merged;
        for (const auto& interval : intervals) {
            if (merged.empty() || interval.first > merged.back().second + 1) {
                merged.push_back(interval);
            } else {
                merged.back().second = std::max(merged.back().second, interval.second);
            }
        }
        intervals = merged;
    }
};