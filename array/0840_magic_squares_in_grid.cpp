#include <array>
#include <bitset>
#include <unordered_set>
#include <vector>

/**
 * A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9 such that each row,
 * column, and both diagonals all have the same sum.
 *
 * Given a row x col grid of integers, how many 3 x 3 contiguous magic square subgrids are there?
 *
 * Note: while a magic square can only contain numbers from 1 to 9, grid may contain numbers up
 * to 15.
 *
 * ! row == grid.length
 * ! col == grid[i].length
 * ! 1 <= row, col <= 10
 * ! 0 <= grid[i][j] <= 15
 */

class Solution
{
public:
    int numMagicSquaresInside(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        int result = 0;
        for (int topX = 0; topX + 2 < m; ++topX) {
            for (int topY = 0; topY + 2 < n; ++topY) {
                result += isValid(topX, topY, grid);
            }
        }
        return result;
    }

private:
    bool isValid(int topX, int topY, const std::vector<std::vector<int>>& grid)
    {
        std::array<int, 3> rowSum{};
        std::array<int, 3> colSum{};
        int diagonal = 0;
        int antiDiagonal = 0;
        std::bitset<10> mask;
        mask[0] = 1;
        for (int i = 0; i <= 2; ++i) {
            for (int j = 0; j <= 2; ++j) {
                const auto& val = grid[i + topX][j + topY];
                if (mask[val] == 1)
                    return false;

                mask[val] = 1;
                rowSum[i] += val;
                colSum[j] += val;
                if (i == j) {
                    diagonal += val;
                }
                if ((i == 1 && j == 1) || std::abs(i - j) == 2) {
                    antiDiagonal += val;
                }
            }
        }
        if (!mask.all())
            return false;

        std::unordered_set<int> set;
        set.insert(rowSum.begin(), rowSum.end());
        set.insert(colSum.begin(), colSum.end());
        set.insert(diagonal);
        set.insert(antiDiagonal);
        return set.size() == 1;
    }
};