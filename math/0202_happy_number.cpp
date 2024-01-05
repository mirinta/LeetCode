#include <unordered_set>

/**
 * Write an algorithm to determine if a number "n" is happy.
 *
 * A happy number is a number defined by the following process:
 *
 * - Starting with any positive integer, replace the number by the sum of the squares of its digits.
 *
 * - Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a
 * cycle which does not include 1.
 *
 * - Those numbers for which this process ends in 1 are happy.
 *
 * Return "true" if "n" is a happy number, and "false" if not.
 */

class Solution
{
public:
    bool isHappy(int n)
    {
        // n = 2 is not a happy number:
        // 2^2 = 4; ----------------------------------
        // 4^2 = 16;                              |
        // 1^2 + 6^2 = 37;                        |
        // 3^2 + 7^2 = 58;                        |
        // 5^2 + 8^2 = 25 + 64 = 89;              |
        // 8^2 + 9^2 = 64 + 81 = 145;             |
        // 1^2 + 4^2 + 5^2 = 1 + 16 + 25 = 42;    |
        // 4^2 + 2^2 = 16 + 4 = 20;               |
        // 2^2 + 0^2 = 4; ---------------------------- 4 appears again
        std::unordered_set<long long> set;
        long long num = n;
        while (true) {
            long long sum = 0;
            while (num) {
                const long long remainder = n % 10;
                sum += remainder * remainder;
                num /= 10;
            }
            if (sum == 1)
                return true;

            if (set.count(sum))
                break;

            set.insert(sum);
            num = sum;
        }
        return false;
    }
};