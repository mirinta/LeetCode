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

        std::vector<std::string> result;
        std::string combination;
        backtrack(result, combination, 0, digits);
        return result;
    }

private:
    static const std::unordered_map<char, std::string> map;
    void backtrack(std::vector<std::string>& result, std::string& combination, int i,
                   const std::string& digits)
    {
        if (combination.size() == digits.size()) {
            result.push_back(combination);
            return;
        }
        for (const auto& c : map.at(digits[i])) {
            combination.push_back(c);
            backtrack(result, combination, i + 1, digits);
            combination.pop_back();
        }
    }
};

const std::unordered_map<char, std::string> Solution::map{{'2', "abc"}, {'3', "def"}, {'4', "ghi"},
                                                          {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"},
                                                          {'8', "tuv"}, {'9', "wxyz"}};