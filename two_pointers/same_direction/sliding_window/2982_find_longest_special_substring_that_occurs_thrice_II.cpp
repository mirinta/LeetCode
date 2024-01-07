#include <array>
#include <string>
#include <unordered_map>

/**
 * You are given a string s that consists of lowercase English letters.
 *
 * A string is called special if it is made up of only a single character. For example, the string
 * "abc" is not special, whereas the strings "ddd", "zz", and "f" are special.
 *
 * Return the length of the longest special substring of s which occurs at least thrice, or -1 if no
 * special substring occurs at least thrice.
 *
 * A substring is a contiguous non-empty sequence of characters within a string.
 *
 * ! 3 <= s.length <= 5 * 10^5
 * ! s consists of only lowercase English letters.
 */

class Solution
{
public:
    int maximumLength(std::string s)
    {
        const int n = s.size();
        // v[i][j] = k, it means there are k special substrings of length j that made up of
        // character 'a'+i
        std::array<std::unordered_map<int, int>, 26> v;
        int result = -1;
        int i = 0;
        while (i < n) {
            int j = i + 1;
            while (j < n && s[j] == s[i]) {
                j++;
            }
            // all characters in s[i:j) are the same,
            // let L = length of s[i:j), based on s[i:j), we can find:
            // - case1: 1 special substring of length L
            // - case2: 2 special substrings of length L-1
            // - case3: 3 special substrings of length L-2, these substrings satisfy the
            // requirements
            // - case4: 4 special substrings of length L-4, these substrings satisfy the
            // requirements
            // ...
            // we only need to consider case1~3, because we want to find the longest length
            const int length = j - i;
            const int index = s[i] - 'a';
            if (++v[index][length] >= 3) {
                result = std::max(result, length);
            }
            if (length - 1 > 0 && (v[index][length - 1] += 2) >= 3) {
                result = std::max(result, length - 1);
            }
            if (length - 2 > 0) {
                result = std::max(result, length - 2);
            }
            i = j;
        }
        return result;
    }
};