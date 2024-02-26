#include <string>
#include <vector>

namespace detail {
std::vector<int> preprocess(const std::string& s)
{
    const int n = s.size();
    std::vector<int> next(n);
    next[0] = 0;
    for (int i = 1; i < n; ++i) {
        int L = next[i - 1];
        while (L >= 1 && s[L] != s[i]) {
            L = next[L - 1];
        }
        next[i] = L + (s[L] == s[i]);
    }
    return next;
}
} // namespace detail

/**
 * @brief Return all occurrences of p (pattern string) within s (text string) using the KMP
 * algorithm.
 *
 * @note Time Complexity = O(M + N), Space Complexity = O(N), where M and N are the lengths of s and
 * p, respectively.
 */
std::vector<int> kmp(const std::string& s, const std::string& p)
{
    const int m = s.size();
    const auto next = detail::preprocess(p);
    int i = 0;
    int j = 0;
    std::vector<int> result;
    while (i < m) {
        if (s[i] == p[j]) {
            i++;
            j++;
        } else if (j > 0) {
            j = next[j - 1];
        } else {
            i++;
        }
        if (j == m) {
            result.push_back(i - m);
            j = next[m - 1];
        }
    }
    return result;
}