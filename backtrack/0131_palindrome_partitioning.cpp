#include <string>
#include <vector>

/**
 * Given a string "s", partition "s" such that every substring of the partition is a palindrome.
 * Return all possible palindrome partitioning of "s".
 */

class Solution
{
public:
    std::vector<std::vector<std::string>> partition(std::string s)
    {
        if (s.empty())
            return {};

        // approach 2: store a 2D table for checking palindrome
        // table[i][j] = s[i:j] is/is not palindrome
        // - table[i][j] = true, if s[i+1:j-1] is a palindrome && s[i] == s[j]
        // std::vector<std::vector<bool>> table(s.size(), std::vector<bool>(s.size(), false));
        // for (int i = s.size() - 1; i >= 0; --i) {
        //     for (int j = i; j < s.size(); ++j) {
        //         if (j == i) {
        //             table[i][j] = true;
        //         } else if (j - i == 1) {
        //             table[i][j] = s[i] == s[j];
        //         } else {
        //             table[i][j] = table[i + 1][j - 1] && s[i] == s[j];
        //         }
        //     }
        // }
        std::vector<std::string> combination;
        backtrack(combination, 0, s);
        return result;
    }

private:
    std::vector<std::vector<std::string>> result;

    void backtrack(std::vector<std::string>& combination, int start, const std::string& s)
    {
        if (start == s.size()) {
            result.push_back(combination);
            return;
        }
        for (int i = start; i < s.size(); ++i) {
            if (isPalindrome(s, start, i)) {
                combination.push_back(s.substr(start, i - start + 1));
                backtrack(combination, i + 1, s);
                combination.pop_back();
            }
        }
    }

    bool isPalindrome(const std::string& s, int low, int high)
    {
        while (low < high) {
            if (s[low++] != s[high--])
                return false;
        }
        return true;
    }
};