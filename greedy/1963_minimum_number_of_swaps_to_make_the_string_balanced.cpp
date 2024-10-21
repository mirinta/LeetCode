#include <cmath>
#include <string>

/**
 * You are given a 0-indexed string s of even length n. The string consists of exactly n / 2 opening
 * brackets '[' and n / 2 closing brackets ']'.
 *
 * A string is called balanced if and only if:
 *
 * - It is the empty string, or
 *
 * - It can be written as AB, where both A and B are balanced strings, or
 *
 * - It can be written as [C], where C is a balanced string.
 *
 * You may swap the brackets at any two indices any number of times.
 *
 * Return the minimum number of swaps to make s balanced.
 *
 * ! n == s.length
 * ! 2 <= n <= 10^6
 * ! n is even.
 * ! s[i] is either '[' or ']'.
 * ! The number of opening brackets '[' equals n / 2, and the number of closing brackets ']' equals
 * ! n / 2.
 */

class Solution
{
public:
    int minSwaps(std::string s)
    {
        // count the num of unbalanced brackets
        int left = 0;
        int unbalanced = 0;
        for (const auto& c : s) {
            if (c == '[') {
                left++;
            } else if (left > 0) {
                left--;
            } else {
                unbalanced++;
            }
        }
        return std::ceil(unbalanced * 1.0 / 2);
    }
};