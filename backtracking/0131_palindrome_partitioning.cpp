#include <string>
#include <vector>

/**
 * Given a string "s", partition "s" such that every substring of the partition is a palindrome.
 * Return all possible palindrome partitioning of "s".
 *
 * ! 1 <= s.length <= 16
 * ! s contains only lowercase English letters.
 */

class Solution
{
public:
    std::vector<std::vector<std::string>> partition(const std::string& s)
    {
        std::vector<std::string> substrings;
        backtrack(substrings, 0, s);
        return result;
    }

private:
    std::vector<std::vector<std::string>> result;

    void backtrack(std::vector<std::string>& substrings, int i, const std::string& s)
    {
        if (i == s.size()) {
            result.push_back(substrings);
            return;
        }
        for (int j = i; j < s.size(); ++j) {
            if (!isPalindrome(i, j, s))
                continue;

            substrings.push_back(s.substr(i, j - i + 1));
            backtrack(substrings, j + 1, s);
            substrings.pop_back();
        }
    }

    bool isPalindrome(int left, int right, const std::string& s)
    {
        for (int i = left, j = right; i <= j; ++i, --j) {
            if (s[i] != s[j])
                return false;
        }
        return true;
    }
};
