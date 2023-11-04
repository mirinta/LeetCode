#include <cmath>
#include <string>

/**
 * Given an integer n, count the total number of digit 1 appearing in all non-negative integers less
 * than or equal to n.
 *
 * ! 0 <= n <= 10^9
 */

class Solution
{
public:
    int countDigitOne(int n)
    {
        // n = X X X X X, in decimal form
        // - f(i, n) = amount of numbers in range [1, n], and the ith digit of them are 1
        // - the final result = sum(f(1,n), f(2,n), ..., f(n,n))
        // - #NOTICE#, i is 1-indexed and it is counted from right to left
        // for example, consider f(3, 23?47):
        // 2 3 ? 4 7
        // Y Y 1 X X
        // - YY in range [0~22] and XX in range [0~99] are valid, 23*100
        // - if YY = 23:
        //   if ? = 0, no valid XX
        //   if ? = 1, XX in range [0~47] are valid, 48
        //   if ? > 1, XX in range [0~99] are valid, 100
        const std::string str = std::to_string(n);
        int result = 0;
        for (int i = 1; i <= str.size(); ++i) {
            const int yy = n / std::pow(10, i);
            result += yy * std::pow(10, i - 1);
            if (str[str.size() - i] - '0' == 1) {
                result += n % static_cast<int>(std::pow(10, i - 1)) + 1;
            } else if (str[str.size() - i] - '0' > 1) {
                result += std::pow(10, i - 1);
            }
        }
        return result;
    }
};