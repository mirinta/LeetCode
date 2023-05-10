#include <vector>

/**
 * The n-queens puzzle is the problem of placing "n" queens on an "n x n" chessboard such that no
 * two queens attack each other.
 *
 * Given an integer "n", return the number of distinct solutions to the n-queens puzzle.
 */

class Solution
{
public:
    int totalNQueens(int n)
    {
        if (n < 1)
            return 0;

        int result = 0;
        // true for 'Q', false for '.' (empty space)
        std::vector<std::vector<bool>> board(n, std::vector(n, false));
        backtrack(board, 0, n, result);
        return result;
    }

private:
    void backtrack(std::vector<std::vector<bool>>& board, int row, int dimension, int& result)
    {
        if (row == dimension) {
            result++;
            return;
        }
        for (int col = 0; col < dimension; ++col) {
            if (!isValid(board, row, col, dimension))
                continue;

            board[row][col] = true;
            backtrack(board, row + 1, dimension, result);
            board[row][col] = false;
        }
    }

    bool isValid(std::vector<std::vector<bool>>& board, int row, int col, int dimension)
    {
        for (int r = row - 1, gap = 1; r >= 0; --r, ++gap) {
            if (board[r][col])
                return false;

            if (int c = col - gap; c >= 0 && board[r][c])
                return false;

            if (int c = col + gap; c < dimension && board[r][c])
                return false;
        }
        return true;
    }
};
