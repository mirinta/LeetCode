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
        Vec2D<std::string> result;
        Vec1D<std::string> board(n, std::string(n, kEmpty));
        backtrack(result, board, 0, n);
        return result;
    }

private:
    template <typename T>
    using Vec1D = std::vector<T>;

    template <typename T>
    using Vec2D = std::vector<std::vector<T>>;

    static constexpr char kQueen = 'Q';
    static constexpr char kEmpty = '.';

    void backtrack(Vec2D<std::string>& result, Vec1D<std::string>& board, int row, int n)
    {
        if (row == n) {
            result.push_back(board);
            return;
        }
        for (int col = 0; col < n; ++col) {
            if (!isValid(row, col, board))
                continue;

            board[row][col] = kQueen;
            backtrack(result, board, row + 1, n);
            board[row][col] = kEmpty;
        }
    }

    bool isValid(int x, int y, const Vec1D<std::string>& board)
    {
        // X   X   X
        //   X X X
        //     Q     <= check this row is valid
        for (int i = x - 1, offset = 1; i >= 0; --i, ++offset) {
            if (board[i][y] == kQueen)
                return false;

            if (y - offset >= 0 && board[i][y - offset] == kQueen)
                return false;

            if (y + offset < board.size() && board[i][y + offset] == kQueen)
                return false;
        }
        return true;
    }
};