#include <algorithm>
#include <string>
#include <vector>

/**
 * Given an array of strings "words", return true if it forms a valid word square.
 *
 * A sequence of strings froms a valid word square if the kth row and column read the same string,
 * where 0 <= k < max(numRows, numColumns).
 */

class Solution
{
public:
    bool validWordSquare(const std::vector<std::string>& words)
    {
        if (words.empty())
            return false;

        // it must be a square matrix
        const size_t m = words.size();
        size_t n = 0;
        for (const auto& word : words) {
            n = std::max(n, word.size());
        }
        if (m != n)
            return false;

        // check the given matrix is symmetric
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                const char c1 = j < words[i].size() ? words[i][j] : '#';
                const char c2 = i < words[j].size() ? words[j][i] : '#';
                if (c1 != c2)
                    return false;
            }
        }
        return true;
    }
};
