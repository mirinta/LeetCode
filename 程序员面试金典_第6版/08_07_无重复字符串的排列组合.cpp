#include <string>
#include <vector>

/**
 * 无重复字符串的排列组合。编写一种方法，计算某字符串的所有排列组合，字符串每个字符均不相同。
 *
 * ! 字符都是英文字母。
 * ! 字符串长度在[1, 9]之间。
 */

class Solution
{
public:
    std::vector<std::string> permutation(std::string s)
    {
        const int n = s.size();
        std::vector<bool> visited(n, false);
        std::string permutation;
        std::vector<std::string> result;
        backtrack(result, permutation, visited, s);
        return result;
    }

private:
    void backtrack(std::vector<std::string>& result, std::string& permutation,
                   std::vector<bool>& visited, const std::string& s)
    {
        const int n = s.size();
        if (permutation.size() == n) {
            result.push_back(permutation);
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (visited[i])
                continue;

            visited[i] = true;
            permutation.push_back(s[i]);
            backtrack(result, permutation, visited, s);
            permutation.pop_back();
            visited[i] = false;
        }
    }
};