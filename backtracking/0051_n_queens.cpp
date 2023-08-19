#include <string>
#include <vector>

/**
 * The n-queens puzzle is the problem of placing "n" queens on an "n x n" chessboard such that no
 * two queens attack each other.
 *
 * Given an integer "n", return all distinct solutions to the n-queens puzzle. You may return the
 * answer in any order.
 *
 * Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and
 * '.' both indicate a queen and an empty space, respectively.
 *
 * ! 1 <= n <= 9
 */

class Solution
{
public:
    std::vector<std::vector<std::string>> solveNQueens(int n)
    {
        if (n < 1)
            return {};

        std::vector<std::string> board(n, std::string(n, k_empty));
        result.clear();
        backtrack(board, 0, n);
        return result;
    }

private:
    static constexpr auto k_queen = 'Q';
    static constexpr auto k_empty = '.';
    std::vector<std::vector<std::string>> result;

    void backtrack(std::vector<std::string>& board, int row, int dimension)
    {
        if (row == dimension) {
            result.push_back(board);
            return;
        }
        for (int col = 0; col < dimension; ++col) {
            if (!isValid(board, row, col, dimension))
                continue;

            board[row][col] = k_queen;
            backtrack(board, row + 1, dimension);
            board[row][col] = k_empty;
        }
    }

    bool isValid(std::vector<std::string>& board, int row, int col, int dimension)
    {
        // for current row, we only need to check the previous rows, i.e., [0, ..., row - 1]
        // because we start from row = 0, the next rows [row + 1, ..., N] are all empty
        // [?  ?  ?] row - 1
        // [   x   ] row
        for (int r = row - 1, gap = 1; r >= 0; --r, ++gap) {
            if (board[r][col] == k_queen)
                return false;

            if (col - gap >= 0 && board[r][col - gap] == k_queen)
                return false;

            if (col + gap < dimension && board[r][col + gap] == k_queen)
                return false;
        }
        return true;
    }
};
