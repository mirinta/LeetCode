#include <string>
#include <vector>

/**
 * A subsequence of a string is a new string that is formed from the original string by deleting
 * some (can be none) of the characters without disturbing the relative positions of the remaining
 * characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
 *
 * Given two strings source and target, return the minimum number of subsequences of source such
 * that their concatenation equals target. If the task is impossible, return -1.
 *
 * ! 1 <= source.length, target.length <= 1000
 * ! source and target consist of lowercase English letters.
 */

class Solution
{
public:
    // time O(26M + N), space O(26M)
    // M and N are lengths of the source string and the target string, respectively
    int shortestWay(std::string source, std::string target)
    {
        // next[i][char] = index of the next "char" after index i,
        // -1 if there's no "char" after index i
        const int m = source.size();
        source.insert(source.begin(), '#');
        std::vector<std::vector<int>> next(m + 1, std::vector<int>(26, -1));
        for (int i = m - 1; i >= 0; --i) {
            // standing at index i,
            // we can see what next[i+1][...] sees
            for (int c = 0; c < 26; ++c) {
                next[i][c] = next[i + 1][c];
            }
            // the only difference is the character at index i+1
            next[i][source[i + 1] - 'a'] = i + 1;
        }
        int i = 0; // for target string
        int j = 0; // for source string
        int count = 1;
        while (i < target.size()) {
            if (next[j][target[i] - 'a'] != -1) {
                // target[i] can be found after s[j]
                j = next[j][target[i] - 'a'];
                i++;
            } else if (j == 0) {
                // next[0][...] contains all characters of the source string
                // next[0][char] = -1 means the "char" is not in the source string
                return -1;
            } else {
                // target[i] can't be found after s[j], we reset j = 0
                // i.e., looking for a new subsequence to make up target[i]
                j = 0;
                count++;
            }
        }
        return count;
    }
};
