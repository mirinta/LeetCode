#include <algorithm>
#include <string>

/**
 * Given two binary strings "a" and "b", return their sum as a binary string.
 *
 * Example:
 * Input: a = "11", b = "1"
 * Output: "100"
 *
 * ! a and b consist only of '0' or '1' characters.
 * ! Each string does not contain leading zeros except for the zero itself.
 */

class Solution
{
public:
    std::string addBinary(const std::string& a, const std::string& b)
    {
        if (a.empty() || b.empty())
            return {};

        int iter1 = a.size() - 1;
        int iter2 = b.size() - 1;
        int carry = 0;
        std::string result;
        while (iter1 >= 0 || iter2 >= 0) {
            if (iter1 < 0) {
                result.push_back(compute(carry, '0', b[iter2--]));
                continue;
            }
            if (iter2 < 0) {
                result.push_back(compute(carry, a[iter1--], '0'));
                continue;
            }
            result.push_back(compute(carry, a[iter1--], b[iter2--]));
        }
        if (carry == 1) {
            result.push_back('1');
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

private:
    char compute(int& carry, char c1, char c2)
    {
        const int sum = (c1 - '0') + (c2 - '0') + carry;
        carry = sum <= 1 ? 0 : 1;
        return (sum == 0 || sum == 2) ? '0' : '1';
    }
};