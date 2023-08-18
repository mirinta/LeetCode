#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given a string containing digits from "2-9" inclusive, return all possible letter combinations
 * that the number could represent. Return the answer in any order.
 *
 * A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1
 * does not map to any letters.
 *
 * ! 0 <= digits.length <= 4
 * ! digits[i] is a digit in the range ['2', '9'].
 */

class Solution
{
public:
    std::vector<std::string> letterCombinations(std::string digits)
    {
        if (digits.empty())
            return {};

        std::unordered_map<char, std::string> map;
        map['2'] = "abc";
        map['3'] = "def";
        map['4'] = "ghi";
        map['5'] = "jkl";
        map['6'] = "mno";
        map['7'] = "pqrs";
        map['8'] = "tuv";
        map['9'] = "wxyz";
        std::vector<std::string> result;
        std::string combination;
        backtrack(result, combination, 0, digits, map);
        return result;
    }

private:
    void backtrack(std::vector<std::string>& result, std::string& combination, int start,
                   const std::string& digits, const std::unordered_map<char, std::string>& map)
    {
        if (start == digits.size()) {
            result.push_back(combination);
            return;
        }
        for (const auto& c : map.at(digits[start])) {
            combination.push_back(c);
            backtrack(result, combination, start + 1, digits, map);
            combination.pop_back();
        }
    }
};