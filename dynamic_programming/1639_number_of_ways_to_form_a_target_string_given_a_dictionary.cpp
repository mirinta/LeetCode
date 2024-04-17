#include <array>
#include <string>
#include <vector>

/**
 * You are given a list of strings of the same length words and a string target.
 *
 * Your task is to form target using the given words under the following rules:
 *
 * - target should be formed from left to right.
 *
 * - To form the ith character (0-indexed) of target, you can choose the kth character of the jth
 * string in words if target[i] = words[j][k].
 *
 * - Once you use the kth character of the jth string of words, you can no longer use the xth
 * character of any string in words where x <= k. In other words, all characters to the left of or
 * at index k become unusuable for every string.
 *
 * - Repeat the process until you form the string target.
 *
 * Notice that you can use multiple characters from the same string in words provided the conditions
 * above are met.
 *
 * Return the number of ways to form target from words. Since the answer may be too large, return it
 * modulo 10^9 + 7.
 *
 * ! 1 <= words.length <= 1000
 * ! 1 <= words[i].length <= 1000
 * ! All strings in words have the same length.
 * ! 1 <= target.length <= 1000
 * ! words[i] and target contain only lowercase English letters.
 */

class Solution
{
public:
    int numWays(std::vector<std::string>& words, std::string target)
    {
        return approach1(words, target);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    int approach1(const std::vector<std::string>& words, const std::string& target)
    {
        const int n = target.size();
        const int w = words[0].size();
        std::vector<std::array<long long, 26>> count(w);
        for (const auto& word : words) {
            for (int k = 0; k < w; ++k) {
                count[k][word[k] - 'a']++;
            }
        }
        std::vector<std::vector<long long>> memo(n, std::vector<long long>(w, -1));
        return dfs(memo, 0, 0, target, count);
    }

    long long dfs(std::vector<std::vector<long long>>& memo, int i, int k,
                  const std::string& target, const std::vector<std::array<long long, 26>>& count)
    {
        if (i == target.size())
            return 1;

        if (k == count.size() || target.size() - i > count.size() - k)
            return 0;

        if (memo[i][k] != -1)
            return memo[i][k];

        const long long case1 = dfs(memo, i, k + 1, target, count);
        const long long case2 =
            dfs(memo, i + 1, k + 1, target, count) * count[k][target[i] - 'a'] % kMod;
        return memo[i][k] = (case1 + case2) % kMod;
    }

    int approach2(const std::vector<std::string>& words, const std::string& target)
    {
        // dp[i][k] = num of ways to form target[0:i-1] using chacaters[0:k-1]
        const int n = target.size();
        const int w = words[0].size();
        // count[k][c] = num of words in the dictionary that word[k] = c
        std::vector<std::array<long long, 26>> count(w);
        for (const auto& word : words) {
            for (int k = 0; k < w; ++k) {
                count[k][word[k] - 'a']++;
            }
        }
        std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(w + 1, 0));
        for (int k = 0; k <= w; ++k) {
            dp[0][k] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int k = 1; k <= w; ++k) {
                const int case1 = dp[i][k - 1];
                const int case2 = dp[i - 1][k - 1] * count[k - 1][target[i - 1] - 'a'] % kMod;
                dp[i][k] = (case1 + case2) % kMod;
            }
        }
        return dp[n][w];
    }
};