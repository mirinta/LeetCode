#include <string>
#include <unordered_map>

/**
 * Given two strings "s" and "t" of lengths "m" and "n" respectively, return the minimum window
 * substring of "s" such that every character in "t" (including duplicates) is included in the
 * window. If there is no such substring, return the empty string "".
 *
 * Example 1:
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
 *
 * Example 2:
 * Input: s = "a", t = "a"
 * Output: "a"
 *
 * Example 3:
 * Input: s = "a", t = "aa"
 * Output: ""
 */

class Solution
{
public:
    // step 1: hold "left" and move "right", expand the window, try to find a "feasible solution"
    //     |------------------|
    // s = | e  b  b  a  n  c | f, t = "abc"
    //     |------------------|
    //    left               right
    //
    // step 2: hold "right" and move "left", shrink the window, try to find a "better solution"
    //             |---------|
    // s = e  b  b | a  n  c | f, t = "abc"
    //             |---------|
    //            left      right
    //
    // step 3: repeat 2 and 3 until "right" touches the end
    std::string minWindow(const std::string& s, const std::string& t)
    {
        if (s.empty() || t.empty() || s.size() < t.size())
            return {};

        // record the "optimal" solution
        int minStart = 0;
        int minLength = INT_MAX;
        // to check a substring is valid
        std::unordered_map<char, int> freq;
        for (const auto& c : t) {
            freq[c]++;
        }
        int counter = freq.size(); // nubmer of unique characters of t
        // sliding window, characters in range [left, right)
        int left = 0;
        int right = 0;
        while (right < s.size()) {
            // expand the window to find a feasible solution
            const auto& charRight = s[right++];
            if (--freq[charRight] == 0) {
                counter--;
            }
            // counter = 0 means a feasible solution is found
            while (counter == 0) {
                // update the optimal solution
                if (right - left < minLength) {
                    minStart = left;
                    minLength = right - left;
                }
                // shrink the window to find a better solution
                const auto& charLeft = s[left++];
                if (++freq[charLeft] > 0) {
                    counter++;
                }
            }
        }
        return minLength == INT_MAX ? "" : s.substr(minStart, minLength);
    }
};