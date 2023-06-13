#include <unordered_map>
#include <vector>

/**
 * Given an integer n, your task is to count how many strings of length n can be formed under the
 * following rules:
 *
 * - Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
 *
 * - Each vowel 'a' may only be followed by an 'e'.
 *
 * - Each vowel 'e' may only be followed by an 'a' or an 'i'.
 *
 * - Each vowel 'i' may not be followed by another 'i'.
 *
 * - Each vowel 'o' may only be followed by an 'i' or a 'u'.
 *
 * - Each vowel 'u' may only be followed by an 'a'.
 *
 * Since the answer may be too large, return it modulo 10^9 + 7.
 *
 * ! 1 <= n <= 2 * 10^4
 */

class Solution
{
public:
    int countVowelPermutation(int n) { return approach2(n); }

private:
    // space optimization of approach1
    int approach2(int n)
    {
        if (n < 1)
            return 0;

        constexpr int kMod = 1e9 + 7;
        long endWithA = 1;
        long endWithE = 1;
        long endWithI = 1;
        long endWithO = 1;
        long endWithU = 1;
        for (int i = 2; i <= n; ++i) {
            auto backupA = endWithA;
            auto backupE = endWithE;
            auto backupI = endWithI;
            auto backupO = endWithO;
            auto backupU = endWithU;

            endWithA = (backupE + backupI + backupU) % kMod;
            endWithE = (backupA + backupI) % kMod;
            endWithI = (backupE + backupO) % kMod;
            endWithO = backupI % kMod;
            endWithU = (backupI + backupO) % kMod;
        }
        return (endWithA + endWithE + endWithI + endWithO + endWithU) % kMod;
    }

    int approach1(int n)
    {
        if (n <= 1)
            return n == 1 ? 5 : 0;

        constexpr int kMod = 1e9 + 7;
        // ends with 'a', X X X a [?], choices = {e}
        // ends with 'e', X X X e [?], choices = {a, i}
        // ends with 'i', X X X i [?], choices = {a, e, o, u}
        // ends with 'o', X X X o [?], choices = {i, u}
        // ends with 'u', X X X u [?], choices = {a}
        // ending letter to valid previous letters
        std::unordered_map<char, std::vector<char>> map;
        map['a'] = {'e', 'i', 'u'};
        map['e'] = {'a', 'i'};
        map['i'] = {'e', 'o'};
        map['o'] = {'i'};
        map['u'] = {'i', 'o'};
        // dp[i][0] = num of permutations with length n that ends with 'a'
        // dp[i][1] = num of permutations with length n that ends with 'e'
        // dp[i][2] = num of permutations with length n that ends with 'i'
        // dp[i][3] = num of permutations with length n that ends with 'o'
        // dp[i][4] = num of permutations with length n that ends with 'u'
        std::vector<std::unordered_map<char, int>> dp(n + 1);
        for (const auto& [end, _] : map) {
            dp[1][end] = 1;
        }
        for (int i = 2; i <= n; ++i) {
            for (const auto& [end, prevLetters] : map) {
                for (const auto& prev : prevLetters) {
                    dp[i][end] += dp[i - 1][prev];
                    dp[i][end] %= kMod;
                }
            }
        }
        int result = 0;
        for (const auto& [_, val] : dp[n]) {
            result += val;
            result %= kMod;
        }
        return result;
    }
};