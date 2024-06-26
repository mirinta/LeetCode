#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

/**
 * A sentence is a string of single-space separated words where each word can contain digits,
 * lowercase letters, and the dollar sign '$'. A word represents a price if it is a sequence of
 * digits preceded by a dollar sign.
 *
 * - For example, "$100", "$23", and "$6" represent prices while "100", "$", and "$1e5" do not.
 *
 * You are given a string sentence representing a sentence and an integer discount. For each word
 * representing a price, apply a discount of discount% on the price and update the word in the
 * sentence. All updated prices should be represented with exactly two decimal places.
 *
 * Return a string representing the modified sentence.
 *
 * Note that all prices will contain at most 10 digits.
 *
 * ! 1 <= sentence.length <= 10^5
 * ! sentence consists of lowercase English letters, digits, ' ', and '$'.
 * ! sentence does not have leading or trailing spaces.
 * ! All words in sentence are separated by a single space.
 * ! All prices will be positive numbers without leading zeros.
 * ! All prices will have at most 10 digits.
 * ! 0 <= discount <= 100
 */

class Solution
{
public:
    std::string discountPrices(std::string sentence, int discount)
    {
        const double factor = 1.0 - 0.01 * discount;
        auto strs = split(sentence, ' ');
        for (auto& s : strs) {
            const auto price = getPrice(s);
            if (price == -1)
                continue;

            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << '$' << price * factor;
            s = stream.str();
        }
        std::string result;
        for (const auto& s : strs) {
            result.append(s);
            result.push_back(' ');
        }
        result.pop_back();
        return result;
    }

private:
    std::vector<std::string> split(const std::string& str, char separator)
    {
        std::istringstream stream(str);
        std::string s;
        std::vector<std::string> result;
        while (std::getline(stream, s, separator)) {
            result.push_back(s);
        }
        return result;
    }

    double getPrice(const std::string& s)
    {
        if (s.size() < 2 || s[0] != '$')
            return -1;

        double result = 0;
        for (int i = 1; i < s.size(); ++i) {
            if (!std::isdigit(s[i]))
                return -1;

            result = result * 10 + (s[i] - '0');
        }
        return result;
    }
};