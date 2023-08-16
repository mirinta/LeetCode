#include <string>

/**
 * Given an integer x, return true if x is a palindrome, and false otherwise.
 *
 * ! -2^31 <= x <= 2^31 - 1
 *
 * ! Follow up: Could you solve it without converting the integer to a string?
 */

class Solution
{
public:
    bool isPalindrome(int x) { return approach2(x); }

private:
    bool approach2(int x)
    {
        if (x < 0)
            return false;

        const int orginalX = x;
        int reverseX = 0;
        while (x) {
            if (reverseX > INT_MAX / 10)
                return false;

            const int digit = x % 10;
            reverseX = reverseX * 10 + digit;
            x /= 10;
        }
        return reverseX == orginalX;
    }

    bool approach1(int x)
    {
        if (x < 0)
            return false;

        const std::string s = std::to_string(x);
        int left = 0;
        int right = s.size() - 1;
        while (left < right) {
            if (s[left] != s[right])
                return false;

            left++;
            right--;
        }
        return true;
    }
};