#include <string>
#include <vector>

/**
 * You are given a string s of lowercase English letters and a 2D integer array shifts where
 * shifts[i] = [starti, endi, directioni]. For every i, shift the characters in s from the index
 * starti to the index endi (inclusive) forward if directioni = 1, or shift the characters backward
 * if directioni = 0.
 *
 * Shifting a character forward means replacing it with the next letter in the alphabet (wrapping
 * around so that 'z' becomes 'a'). Similarly, shifting a character backward means replacing it with
 * the previous letter in the alphabet (wrapping around so that 'a' becomes 'z').
 *
 * Return the final string after all such shifts to s are applied.
 *
 * ! 1 <= s.length, shifts.length <= 5 * 10^4
 * ! shifts[i].length == 3
 * ! 0 <= starti <= endi < s.length
 * ! 0 <= directioni <= 1
 * ! s consists of lowercase English letters.
 */

class Solution
{
public:
    std::string shiftingLetters(std::string s, std::vector<std::vector<int>>& shifts)
    {
        const int n = s.size();
        std::vector<int> diff(n); // diff[i] = shift[i]-shift[i-1]
        for (const auto& shift : shifts) {
            const auto& start = shift[0];
            const auto& end = shift[1];
            const auto delta = shift[2] == 0 ? -1 : 1;
            diff[start] += delta;
            if (end + 1 < n) {
                diff[end + 1] -= delta;
            }
        }
        std::string result;
        result.reserve(n);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                diff[i] += diff[i - 1];
            }
            const int delta = diff[i] + s[i] - 'a';
            if (delta >= 0 || delta % 26 == 0) {
                result.push_back(delta % 26 + 'a');
            } else {
                result.push_back(delta % 26 + 26 + 'a');
            }
        }
        return result;
    }
};
