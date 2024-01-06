#include <algorithm>
#include <string>
#include <vector>

/**
 * You are given an integer n, a 0-indexed string array words, and a 0-indexed array groups, both
 * arrays having length n.
 *
 * The hamming distance between two strings of equal length is the number of positions at which the
 * corresponding characters are different.
 *
 * You need to select the longest subsequence from an array of indices [0, 1, ..., n - 1], such that
 * for the subsequence denoted as [i0, i1, ..., ik - 1] having length k, the following holds:
 *
 * - For adjacent indices in the subsequence, their corresponding groups are unequal, i.e.,
 * groups[ij] != groups[ij + 1], for each j where 0 < j + 1 < k.
 *
 * - words[ij] and words[ij + 1] are equal in length, and the hamming distance between them is 1,
 * where 0 < j + 1 < k, for all indices in the subsequence.
 *
 * Return a string array containing the words corresponding to the indices (in
 * order) in the selected subsequence. If there are multiple answers, return any of them.
 *
 * A subsequence of an array is a new array that is formed from the original array by deleting some
 * (possibly none) of the elements without disturbing the relative positions of the remaining
 * elements.
 *
 * Note: strings in words may be unequal in length.
 *
 * ! 1 <= n == words.length == groups.length <= 1000
 * ! 1 <= words[i].length <= 10
 * ! 1 <= groups[i] <= n
 * ! words consists of distinct strings.
 * ! words[i] consists of lowercase English letters.
 */

class Solution
{
public:
    std::vector<std::string> getWordsInLongestSubsequence(int n, std::vector<std::string>& words,
                                                          std::vector<int>& groups)
    {
        // dp[i] = the longest valid indices ending at words[i]
        std::vector<std::vector<int>> dp(n);
        for (int i = 0; i < n; ++i) {
            int maxLength = 0;
            int maxIndex = -1;
            for (int j = i - 1; j >= 0; --j) {
                if (groups[i] != groups[j] && isValid(words[i], words[j])) {
                    if (dp[j].size() > maxLength) {
                        maxIndex = j;
                        maxLength = dp[j].size();
                    }
                }
            }
            if (maxIndex >= 0) {
                dp[i] = dp[maxIndex];
            }
            dp[i].push_back(i);
        }
        const auto indices =
            *std::max_element(dp.begin(), dp.end(),
                              [](const auto& v1, const auto& v2) { return v1.size() < v2.size(); });
        std::vector<std::string> result;
        result.reserve(indices.size());
        for (const auto& i : indices) {
            result.push_back(words[i]);
        }
        return result;
    }

private:
    bool isValid(const std::string& s1, const std::string& s2)
    {
        if (s1.size() != s2.size())
            return false;

        int count = 0;
        for (int i = 0; i < s1.size(); ++i) {
            count += s1[i] != s2[i];
            if (count > 1)
                return false;
        }
        return count == 1;
    }
};