#include <string>
#include <unordered_map>

/**
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
 *
 * Symbol   Value
 * I        1
 * V        5
 * X        10
 * L        50
 * C        100
 * D        500
 * M        1000
 *
 * For example, 2 is written as II in Roman numeral, just two ones added together. 12 is written as
 * XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.
 *
 * Roman numerals are usually written largest to smallest from left to right. However, the numeral
 * for four is not IIII. Instead, the number four is written as IV. Because the one is before the
 * five we subtract it making four. The same principle applies to the number nine, which is written
 * as IX. There are six instances where subtraction is used:
 *
 * - I can be placed before V (5) and X (10) to make 4 and 9.
 *
 * - X can be placed before L (50) and C (100) to make 40 and 90.
 *
 * - C can be placed before D (500) and M (1000) to make 400 and 900.
 *
 * Given a roman numeral, convert it to an integer.
 *
 * ! s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
 * ! It is guaranteed that s is a valid roman numeral in the range [1, 3999].
 */

class Solution
{
public:
    int romanToInt(const std::string& s)
    {
        if (s.empty())
            return 0;

        std::unordered_map<char, int> map;
        map['I'] = 1;
        map['V'] = 5;
        map['X'] = 10;
        map['L'] = 50;
        map['C'] = 100;
        map['D'] = 500;
        map['M'] = 1000;
        // M [C] M [X] C [I] V
        // - if letter[i] < letter[i+1], the value should be subtracted from the result
        // - otherwise,  add it to result
        int result = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            const auto& letter = s[i];
            if (!map.count(letter))
                return 0;

            if (i + 1 < s.size() && map[letter] < map[s[i + 1]]) {
                result -= map[letter];
            } else {
                result += map[letter];
            }
        }
        return result;
    }
};