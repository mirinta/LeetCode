#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a string s and a positive integer k.
 *
 * Let vowels and consonants be the number of vowels and consonants in a string.
 *
 * A string is beautiful if:
 *
 * - vowels == consonants.
 *
 * - (vowels * consonants) % k == 0, in other terms the multiplication of vowels and consonants is
 * divisible by k. Return the number of non-empty beautiful substrings in the given string s.
 *
 * A substring is a contiguous sequence of characters in a string.
 *
 * Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
 *
 * Consonant letters in English are every letter except vowels.
 *
 * ! 1 <= s.length <= 5 * 10^4
 * ! 1 <= k <= 1000
 * ! s consists of only English lowercase letters.
 */

class Solution
{
public:
    long long beautifulSubstrings(std::string s, int k)
    {
        // mark vowels as +1 and consonants as -1
        // - consider a substring s[j:i] that satisfies #vowels = #consonants
        // - marker_sum[j:i] = 0 = marker_sum[0:i] - marker_sum[0:j-1]
        // - thus, we have marker_sum[0:i] = marker_sum[0:j-1]
        //
        // it implies:
        // - standing at i, we have mark_sum[0:i]
        // - if there exists j such that mark_sum[0:j] = marker_sum[0:i]
        // - then s[j+1:i] is a substring that satisfies #vowels = #consonants
        // - the length of s[j+1:i] is i - j
        //
        // #vowels + #consonants = L, L is the length of a substring
        // according to the constraints:
        // - #vowels = L/2
        // - #vowels * #vowels % k = (L/2)^2 % k = 0
        // - we want L^2 % 4k = 0
        //
        // we can find the smallest L such that L^2 % 4k = 0,
        // then we need to consider L, 2L, 3L, ...
        // - let i - j = xL, x = 1, 2, 3, ...
        // - then (i - j) % L = 0, it means i % L = j % L
        const int n = s.size();
        int length = 1;
        while (length * length % (4 * k) != 0) {
            length++;
        }
        long long result = 0;
        std::unordered_map<int, std::unordered_map<int, int>> map;
        // base case: marker_sum[0:i] = 0, L = i - 1, i % L = L - 1
        map[0][length - 1] = 1;
        for (int i = 0, sum = 0; i < n; ++i) {
            sum += isVowel(s[i]) ? 1 : -1;
            if (map.count(sum) && map[sum].count(i % length)) {
                result += map[sum][i % length];
            }
            map[sum][i % length]++;
        }
        return result;
    }

private:
    bool isVowel(char c) { return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; }
};