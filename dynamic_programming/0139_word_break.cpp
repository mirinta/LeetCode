#include <string>
#include <unordered_set>
#include <vector>

/**
 * Given a string "s" and a dictionary of strings "wordDict", return true if "s" can be segmented
 * into a space-separated sequence of one or more dictionary words.
 *
 * Note that the same word in the dictionary may be used multiple times in the segmentation.
 */

class Solution
{
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict)
    {
        // approach 1: DP
        const std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());
        std::vector<bool> dp(1 + s.size(), false); // dp[i] = s[0:i) can be wordBreak
        dp[0] = true;
        for (int i = 1; i <= s.size(); ++i) {
            // split s[0:i) to s[0:j) and s[j:i)
            // if s[0:j) can be wordBreak, i.e., dp[j] = true
            // and s[j:i) is in the dictionary, then dp[i] = true
            for (int j = 0; j < i; ++j) {
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
        // approach 2: recursion + memorization
        // memo[i] = -1/0/1, -1 = not calculated, 0 = false, 1 = true
        // const std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());
        // std::vector<int> memo(s.size(), -1);
        // return dp(0, memo, s, dict);
    }

private:
    // check s[i:...] can be wordBreak
    bool dp(int start, std::vector<int>& memo, const std::string& s,
            const std::unordered_set<std::string>& dict)
    {
        if (start == s.length())
            return true;

        if (memo[start] != -1)
            return memo[start];

        // if s[i:k] is in the dictionary, and s[k+1:...] can be wordBreak
        // then s[i:...] can be wordBreak
        for (int k = start; k < s.size(); ++k) {
            const auto length = k - start + 1;
            if (!dict.count(s.substr(start, length)))
                continue;

            if (dp(k + 1, memo, s, dict)) {
                memo[start] = 1;
                return true;
            }
        }
        memo[start] = 0;
        return false;
    }
};