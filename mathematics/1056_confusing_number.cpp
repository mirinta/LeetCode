#include <string>
#include <unordered_map>

/**
 * A confusing number is a number that when rotated 180 degrees becomes a different number with each
 * digit valid.
 *
 * We can rotate digits of a number by 180 degrees to form new digits.
 *
 * - When 0, 1, 6, 8, and 9 are rotated 180 degrees, they become 0, 1, 9, 8, and 6 respectively.
 *
 * - When 2, 3, 4, 5, and 7 are rotated 180 degrees, they become invalid.
 *
 * Note that after rotating a number, we can ignore leading zeros.
 *
 * - For example, after rotating 8000, we have 0008 which is considered as just 8.
 *
 * Given an integer n, return true if it is a confusing number, or false otherwise.
 */

class Solution
{
public:
    bool confusingNumber(int n)
    {
        // n = 1 or 0, is not confusing number
        if (n <= 1)
            return false;

        std::unordered_map<char, char> map;
        map['0'] = '0';
        map['1'] = '1';
        map['6'] = '9';
        map['8'] = '8';
        map['9'] = '6';
        const auto before = std::to_string(n);
        std::string after;
        for (const auto& digit : before) {
            if (!map.count(digit))
                return false;

            after.push_back(map[digit]);
        }
        std::reverse(after.begin(), after.end());
        return std::stoi(after) != n;
    }
};