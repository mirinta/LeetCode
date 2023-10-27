#include <string>
#include <vector>

/**
 * Given an array of keywords words and a string s, make all appearances of all keywords words[i] in
 * s bold. Any letters between <b> and </b> tags become bold.
 *
 * Return s after adding the bold tags. The returned string should use the least number of tags
 * possible, and the tags should form a valid combination.
 *
 * ! 1 <= s.length <= 500
 * ! 0 <= words.length <= 50
 * ! 1 <= words[i].length <= 10
 * ! s and words[i] consist of lowercase English letters.
 *
 * ! This question is the same as 616.
 */

class Solution
{
public:
    std::string boldWords(std::vector<std::string>& words, std::string s)
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