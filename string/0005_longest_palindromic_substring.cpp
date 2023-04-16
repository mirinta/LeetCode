#include <string>

/**
 * Given a string "s", return the longest palindromic substring in "s".
 */

class Solution
{
public:
    std::string longestPalindrome(const std::string& s)
    {
        // loop through each character, use it as a center to find palindrome:
        // START, ..., left, right, ..., END
        //             <-|    |->
        // - case 1: for even length palindrome, left = right
        // - case 2: for odd length palindrome, left + 1 = right
        std::string result{};
        for (size_t i = 0; i < s.size(); ++i) {
            const auto even = findPalindrome(s, i, i);
            const auto odd = findPalindrome(s, i, i + 1);
            result = result.size() > even.size() ? result : even;
            result = result.size() > odd.size() ? result : odd;
        }
        return result;
    }

private:
    std::string findPalindrome(const std::string& s, int left, int right)
    {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        }
        // when the loop ends:
        // START, ..., left, (PALINDROME), right, ..., END
        return s.substr(left + 1, right - left - 1);
    }
};