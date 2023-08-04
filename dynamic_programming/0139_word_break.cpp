#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Given a string "s" and a dictionary of strings "wordDict", return true if "s" can be segmented
 * into a space-separated sequence of one or more dictionary words.
 *
 * Note that the same word in the dictionary may be used multiple times in the segmentation.
 *
 * ! 1 <= s.length <= 300
 * ! 1 <= wordDict.length <= 1000
 * ! 1 <= wordDict[i].length <= 20
 * ! s and wordDict[i] consist of only lowercase English letters.
 * ! All the strings of wordDict are unique.
 */

class Solution
{
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict)
    {
        return approach3(s, wordDict);
    }

private:
    // DP + Hash Set
    bool approach3(std::string& s, std::vector<std::string>& wordDict)
    {
        std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());
        const int n = s.size();
        // dp[i] = s[0:i) can be "word break"
        std::vector<int> dp(n + 1, false);
        dp[0] = true;
        for (int i = 1; i <= n; ++i) {
            // 0 X X X X j-1 j X X X X i-1 i
            // |<--dp[j]-->| |<---word-->|
            // |<---------dp[i]--------->|
            for (int j = 0; j < i; ++j) {
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }

    struct TrieNode
    {
        bool isEnd = false;
        std::unordered_map<char, TrieNode*> next;
    };

    // DP + Trie
    bool approach2(std::string& s, std::vector<std::string>& wordDict)
    {
        auto* root = new TrieNode();
        for (const auto& word : wordDict) {
            auto* node = root;
            for (const auto& c : word) {
                if (!node->next.count(c)) {
                    node->next[c] = new TrieNode();
                }
                node = node->next[c];
            }
            node->isEnd = true;
        }
        const int n = s.size();
        std::vector<bool> dp(n, false); // dp[i] = s[0:i] can be "word break"
        for (int i = 0; i < n; ++i) {
            // 0 X X i-1 i X X X j
            // |<----->| |<----->|
            // if s[0:j] can be "word break":
            // - s[0:i-1] can be "word break", and
            // - s[i:j] is in the dictionary
            if (i == 0 || dp[i - 1]) {
                auto* node = root;
                for (int j = i; j < n; ++j) {
                    if (!node->next.count(s[j]))
                        break;

                    node = node->next[s[j]];
                    if (node->isEnd) {
                        dp[j] = true;
                    }
                }
            }
        }
        return dp[n - 1];
    }

    // DP
    bool approach1(std::string& s, std::vector<std::string>& wordDict)
    {
        const int n = s.size();
        // dp[i] = s[0:i) can be "word break"
        std::vector<bool> dp(n + 1, false);
        dp[0] = true;
        for (int i = 1; i <= n; ++i) {
            // 0 X X X X j-1 j X X X X i-1 i
            // |<--dp[j]-->| |<---word-->|
            // |<---------dp[i]--------->|
            for (const auto& word : wordDict) {
                const int length = word.size();
                const int j = i - length;
                if (j >= 0 && s.substr(j, length) == word && dp[j]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};
