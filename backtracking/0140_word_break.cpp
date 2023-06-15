#include <string>
#include <unordered_set>
#include <vector>

/**
 * Given a string "s" and a dictionary of strings "wordDict", add spaces in "s" to construct a
 * sentence where each word is a valid dictionary word. Return all such possible sentences in any
 * order.
 *
 * Note that the same word in the dictionary may be reused multiple times in the segmentation.
 */

class Solution
{
public:
    std::vector<std::string> wordBreak(std::string s, std::vector<std::string>& wordDict)
    {
        const std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());
        std::vector<std::string> track;
        backtrack(track, 0, s, dict);
        return result;
    }

private:
    std::vector<std::string> result;

    void backtrack(std::vector<std::string>& track, int start, const std::string& s,
                   const std::unordered_set<std::string>& dict)
    {
        if (start == s.size()) {
            std::string sentence;
            for (size_t i = 0; i < track.size(); ++i) {
                sentence.append(track[i]);
                if (i + 1 < track.size()) {
                    sentence.push_back(' ');
                }
            }
            result.push_back(std::move(sentence));
            return;
        }
        for (const auto& word : dict) {
            if (start + word.size() > s.size())
                continue;

            if (s.substr(start, word.size()) != word)
                continue;

            track.push_back(word);
            backtrack(track, start + word.size(), s, dict);
            track.pop_back();
        }
    }
};