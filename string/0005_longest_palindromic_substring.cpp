#include <string>

/**
 * Given a string "s", return the longest palindromic substring in "s".
 *
 * ! 1 <= s.length <= 1000
 * ! s consist of only digits and English letters.
 */

class Solution
{
public:
    // time O(N^2), space O(1)
    std::string longestPalindrome(std::string s)
    {
        if (s.size() == 1)
            return s;

        std::string result;
        for (int i = 0; i < s.size(); ++i) {
            const auto evenLengthPalindrome = getPalindrome(i, i + 1, s);
            const auto oddLengthPalindrome = getPalindrome(i, i, s);
            if (evenLengthPalindrome.size() > result.size()) {
                result = evenLengthPalindrome;
            }
            if (oddLengthPalindrome.size() > result.size()) {
                result = oddLengthPalindrome;
            }
        }
        return result;
    }

private:
    std::string getPalindrome(int leftStart, int rightStart, const std::string& s)
    {
        if (s[leftStart] != s[rightStart])
            return {};

        // X X X X L R X X X X
        //       <-| |->
        int left = leftStart;
        int right = rightStart;
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        } // the final answer is in range (left, right)
        return s.substr(left + 1, right - left - 1);
    }
};