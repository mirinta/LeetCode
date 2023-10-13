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
    std::vector<std::string> letterCombinations(const std::string& digits)
    {
        if (digits.empty())
            return {};

        std::string path;
        backtrack(path, 0, digits);
        return result;
    }

private:
    std::vector<std::string> result;

    void backtrack(std::string& path, int i, const std::string& digits)
    {
        if (i == digits.size()) {
            result.push_back(path);
            return;
        }
        static const std::unordered_map<char, std::string> map{
            {'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
            {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
        for (const auto& c : map.at(digits[i])) {
            path.push_back(c);
            backtrack(path, i + 1, digits);
            path.pop_back();
        }
    }
};