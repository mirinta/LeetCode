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
        if (n == 1)
            return 1;

        // 0 for empty space, 1 for queen
        std::vector<std::vector<int>> board(n, std::vector<int>(n, 0));
        int result = 0;
        backtrack(result, board, 0);
        return result;
    }

private:
    void backtrack(int& result, std::vector<std::vector<int>>& board, int row)
    {
        if (row == board.size()) {
            result++;
            return;
        }
        for (int col = 0; col < board[row].size(); ++col) {
            if (isValid(row, col, board)) {
                board[row][col] = 1;
                backtrack(result, board, row + 1);
                board[row][col] = 0;
            }
        }
    }

    bool isValid(int row, int col, const std::vector<std::vector<int>>& board)
    {
        for (int checkRow = row - 1, offset = 1; checkRow >= 0; --checkRow, ++offset) {
            // row i-2: | ? _ ? _ ? |
            // row i-1: | _ ? ? ? _ |
            // row   i: | _ _ X _ _ |
            if (board[checkRow][col] == 1)
                return false;

            if (col + offset < board[checkRow].size() && board[checkRow][col + offset] == 1)
                return false;

            if (col - offset >= 0 && board[checkRow][col - offset] == 1)
                return false;
        }
        return true;
    }
};
