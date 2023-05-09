#include <vector>

/**
 * Given two sparse matrices "mat1" of size m x k and "mat2" of size k x n, return the result of
 * "mat1 x mat2". You may assume that multiplication is always possible.
 *
 * ! m == mat1.length
 * ! k == mat1[i].length == mat2.length
 * ! n == mat2[i].length
 * ! 1 <= m, n, k
 */

class Solution
{
public:
    std::vector<std::vector<int>> multiply(std::vector<std::vector<int>>& mat1,
                                           std::vector<std::vector<int>>& mat2)
    {
        if (mat1.empty() || mat2.empty())
            return {};

        // A_mk x B_kn = C_mn
        // c_ij = sum(a_ip * b_pj), p from 0 to k - 1
        const auto m = mat1.size();
        const auto k = mat2.size();
        const auto n = mat2[0].size();
        std::vector<std::vector<int>> result(m, std::vector<int>(n, 0));
        for (size_t i = 0; i < m; ++i) {
            for (size_t p = 0; p < k; ++p) {
                if (mat1[i][p] == 0)
                    continue;

                for (size_t j = 0; j < n; ++j) {
                    if (mat2[p][j] == 0)
                        continue;

                    result[i][j] += mat1[i][p] * mat2[p][j];
                }
            }
        }
        return result;
    }
};