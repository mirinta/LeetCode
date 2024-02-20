#include <string>
#include <vector>

/**
 * A wonderful string is a string where at most one letter appears an odd number of times.
 *
 * - For example, "ccjjc" and "abab" are wonderful, but "ab" is not.
 *
 * Given a string word that consists of the first ten lowercase English letters ('a' through 'j'),
 * return the number of wonderful non-empty substrings in word. If the same substring appears
 * multiple times in word, then count each occurrence separately.
 *
 * A substring is a contiguous sequence of characters in a string.
 *
 * ! 1 <= word.length <= 10^5
 * ! word consists of lowercase English letters from 'a' to 'j'.
 */

class Solution
{
public:
    long long wonderfulSubstrings(std::string word)
    {
        const int n = word.size();
        std::vector<long long> count(1 << 10, 0); // count[i] = num of occurrences of state i
        count[0] = 1;
        int state = 0; // state[x] = whether the xth letter appears an odd num of times
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            state ^= 1 << (word[i] - 'a');
            // case 1: all letters appear an even num of times in word[j+1:i]
            result += count[state];
            // case 2: only one letter appears an odd num of times in word[j+1:i]
            for (int k = 0; k < 10; ++k) {
                result += count[state ^ (1 << k)];
            }
            count[state]++;
        }
        return result;
    }
};