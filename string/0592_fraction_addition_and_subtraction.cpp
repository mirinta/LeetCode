#include <numeric>
#include <string>
#include <vector>

/**
 * Given a string expression representing an expression of fraction addition and subtraction, return
 * the calculation result in string format.
 *
 * The final result should be an irreducible fraction. If your final result is an integer, change it
 * to the format of a fraction that has a denominator 1. So in this case, 2 should be converted to
 * 2/1.
 *
 * ! The input string only contains '0' to '9', '/', '+' and '-'. So does the output.
 * ! Each fraction (input and output) has the format ±numerator/denominator. If the first input
 *   fraction or the output is positive, then '+' will be omitted.
 * ! The input only contains valid irreducible fractions, where the numerator and denominator of
 *   each fraction will always be in the range [1, 10]. If the denominator is 1, it means this
 *   fraction is actually an integer in a fraction format defined above.
 * ! The number of given fractions will be in the range [1, 10].
 * ! The numerator and denominator of the final result are guaranteed to be valid and in the range
 *   of 32-bit int.
 */

class Solution
{
public:
    std::string fractionAddition(std::string expression)
    {
        if (std::isdigit(expression[0])) {
            expression.insert(expression.begin(), '+');
        }
        const int n = expression.size();
        auto getValue = [&](int& i) {
            int val = 0;
            while (i < n && std::isdigit(expression[i])) {
                val = val * 10 + (expression[i++] - '0');
            }
            return val;
        };
        std::vector<int> numerators;
        std::vector<int> denominators;
        int i = 0;
        while (i < n) {
            const int sign = expression[i++] == '+' ? 1 : -1;
            numerators.push_back(sign * getValue(i));
            i++;
            denominators.push_back(getValue(i));
        }
        int lcm = 1;
        for (const auto& val : denominators) {
            lcm = std::lcm(lcm, val);
        }
        int sum = 0;
        for (int i = 0; i < numerators.size(); ++i) {
            sum += numerators[i] * lcm / denominators[i];
        }
        const int gcd = std::gcd(lcm, sum);
        sum /= gcd;
        lcm /= gcd;
        return std::to_string(sum) + '/' + std::to_string(lcm);
    }
};
