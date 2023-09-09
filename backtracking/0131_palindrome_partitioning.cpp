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
    std::vector<std::vector<std::string>> partition(std::string s)
    {
        const int n = s.size();
        // dynamic programming: memo[i][j] = whether s[i:j] is palindrome
        Vec2D<bool> memo(n, Vec1D<bool>(n, false));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                // i i+1 X X X X X X X j-1 j
                //   |<---dp[i+1][j-1]-->|
                // |<-------dp[i][j]------>|
                if (i == j) {
                    memo[i][j] = true;
                } else if (j - i == 1) {
                    memo[i][j] = s[i] == s[j];
                } else {
                    memo[i][j] = s[i] == s[j] && memo[i + 1][j - 1];
                }
            }
        }
        Vec2D<std::string> result;
        Vec1D<std::string> substring;
        backtrack(result, substring, 0, s, memo);
        return result;
    }

private:
    template <typename T>
    using Vec2D = std::vector<std::vector<T>>;

    template <typename T>
    using Vec1D = std::vector<T>;

    void backtrack(Vec2D<std::string>& result, Vec1D<std::string>& substring, int start,
                   const std::string& s, const Vec2D<bool>& memo)
    {
        if (start == s.size()) {
            result.push_back(substring);
            return;
        }
        for (int end = start; end < s.size(); ++end) {
            if (memo[start][end]) { // or isPalindrome(start, end, s)
                substring.push_back(s.substr(start, end - start + 1));
                backtrack(result, substring, end + 1, s, memo);
                substring.pop_back();
            }
        }
    }

    bool isPalindrome(int start, int end, const std::string& s)
    {
        for (int i = start, j = end; i < end; ++i, --j) {
            if (s[i] != s[j])
                return false;
        }
        return true;
    }
};