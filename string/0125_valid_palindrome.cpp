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
    bool isPalindrome(const std::string& s)
    {
        // X X X X X
        // ^       ^
        // i       j
        const auto n = s.size();
        if (n <= 1)
            return true;

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

            if (toLowerCase(s[left]) != toLowerCase(s[right]))
                return false;

            left++;
            right--;
        }
        return true;
    }

private:
    bool isAlphaNumeric(char c)
    {
        if ('0' <= c && c <= '9') {
            return true;
        } else if ('a' <= c && c <= 'z') {
            return true;
        } else if ('A' <= c && c <= 'Z') {
            return true;
        } else {
            return false;
        }
    }

    char toLowerCase(char c)
    {
        constexpr char kOffset = 'A' - 'a';
        if ('A' <= c && c <= 'Z')
            return c - kOffset;

        return c;
    }
};