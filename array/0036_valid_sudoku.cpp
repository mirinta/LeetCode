#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according
 * to the following rules:
 *
 * - Each row must contain the digits 1-9 without repetition.
 *
 * - Each column must contain the digits 1-9 without repetition.
 *
 * - Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
 *
 * Note:
 *
 * - A Sudoku board (partially filled) could be valid but is not necessarily solvable.
 *
 * - Only the filled cells need to be validated according to the mentioned rules.
 *
 * ! board.length == 9
 * ! board[i].length == 9
 * ! board[i][j] is a digit 1-9 or '.'.
 */

class Solution
{
public:
    bool isValidSudoku(std::vector<std::vector<char>>& board)
    {
        const int n = board.size();
        std::unordered_set<char> set;
        // check each row
        for (int i = 0; i < n; ++i) {
            set.clear();
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == '.')
                    continue;

                if (!set.insert(board[i][j]).second)
                    return false;
            }
        }
        // check each column
        for (int j = 0; j < n; ++j) {
            set.clear();
            for (int i = 0; i < n; ++i) {
                if (board[i][j] == '.')
                    continue;

                if (!set.insert(board[i][j]).second)
                    return false;
            }
        }
        // check each 3x3 grid
        std::unordered_map<int, std::unordered_set<int>> map;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == '.')
                    continue;

                const int idx = i / 3 * 3 + j / 3;
                if (!map[idx].insert(board[i][j]).second)
                    return false;
            }
        }
        return true;
    }
};