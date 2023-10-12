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
        std::vector<std::string> palindromes;
        backtrack(palindromes, 0, s);
        return result;
    }

private:
    std::vector<std::vector<std::string>> result;

    void backtrack(std::vector<std::string>& palindromes, int start, const std::string& s)
    {
        if (start == s.size()) {
            result.push_back(palindromes);
            return;
        }
        // substring: s[start:end]
        for (int end = start; end < s.size(); ++end) {
            if (isPalindrome(start, end, s)) {
                palindromes.push_back(s.substr(start, end - start + 1));
                backtrack(palindromes, end + 1, s);
                palindromes.pop_back();
            }
        }
    }

    bool isPalindrome(int start, int end, const std::string& s)
    {
        while (start <= end) {
            if (s[start] != s[end])
                return false;

            start++;
            end--;
        }
        return true;
    }
};
