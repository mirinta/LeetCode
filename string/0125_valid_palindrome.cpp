#include <string>

/**
 * A phrase is a palindrome if, after converting all uppercase letters into lowercase and removing
 * all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters
 * include letters and numbers.
 *
 * Given a string "s", return true if it is a palindrome, or false otherwise.
 *
 * ! 1 <= s.length <= 2 * 10^5
 * ! s consists only of printable ASCII characters.
 */

class Solution
{
public:
    bool isPalindrome(std::string s)
    {
        const int n = s.size();
        int left = 0;
        int right = n - 1;
        while (true) {
            while (left < n && !isAlphaNumeric(s[left])) {
                left++;
            }
            while (right >= 0 && !isAlphaNumeric(s[right])) {
                right--;
            }
            if (left >= right)
                break;

            if (toLowercase(s[left]) != toLowercase(s[right]))
                return false;

            left++;
            right--;
        }
        return true;
    }

private:
    bool isAlphaNumeric(char c)
    {
        return ('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
    }

    char toLowercase(char c)
    {
        if ('A' <= c && c <= 'Z')
            return c - ('A' - 'a');

        return c;
    }
};