#include <string>

/**
 * Given a string s of zeros and ones, return the maximum score after splitting the string into two
 * non-empty substrings (i.e. left substring and right substring).
 *
 * The score after splitting a string is the number of zeros in the left substring plus the number
 * of ones in the right substring.
 *
 * ! 2 <= s.length <= 500
 * ! The string s consists of characters '0' and '1' only.
 */

class Solution
{
public:
    int maxScore(std::string s)
    {
        int totalOnes = 0;
        for (const auto& c : s) {
            if (c == '1') {
                totalOnes++;
            }
        }
        int result = 0;
        for (int i = 0, zeros = 0; i < s.size() - 1; ++i) {
            zeros += s[i] == '0' ? 1 : 0;
            result = std::max(result, zeros + totalOnes - (i + 1 - zeros));
        }
        return result;
    }
};