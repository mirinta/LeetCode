#include <vector>
#include <string>

/**
 * Given a string containing digits from "2-9" inclusive, return all possible letter combinations
 * that the number could represent. Return the answer in any order.
 *
 * A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1
 * does not map to any letters.
 */

class Solution
{
public:
    std::vector<std::string> letterCombinations(std::string digits)
    {
        if (digits.empty())
            return {};

        const auto map = buildMap();
        std::string combination;
        backtrack(combination, 0, digits, map);
        return result;
    }

private:
    std::vector<std::string> result;

    std::vector<std::string> buildMap()
    {
        std::vector<std::string> map(11);
        map[2] = "abc";
        map[3] = "def";
        map[4] = "ghi";
        map[5] = "jkl";
        map[6] = "mno";
        map[7] = "pqrs";
        map[8] = "tuv";
        map[9] = "wxyz";
        return map;
    }

    void backtrack(std::string& combination, int start, const std::string& digits,
                   const std::vector<std::string>& map)
    {
        if (combination.size() == digits.size()) {
            result.push_back(combination);
            return;
        }
        const auto& letters = map[digits[start] - '0'];
        for (const auto& letter : letters) {
            combination.push_back(letter);
            backtrack(combination, start + 1, digits, map);
            combination.pop_back();
        }
    }
};