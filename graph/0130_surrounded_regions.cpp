#include <vector>

/**
 * Given an m x n matrix "board" containing "X" and "O", capture all regions that are
 * 4-directionally surrounded by "X".
 *
 * A region is captured by flipping all "O"'s into "X"s in that surrounded region.
 */

// All "O"s on the border, as well as "O"s directly or indirectly connected to them, should not be
// flipped. To solve the problem:
// 1. set each "O" that should not be flipped to "#" (using DFS)
// 2. set each "O" to "X"
// 3. set each "#" back to "O"

class Solution
{
public:
    // All "O"s on the border, as well as "O"s directly or indirectly connected to them, should not
    // be flipped. To solve the problem:
    // 1. set each "O" that should not be flipped to "#" (using DFS)
    // 2. set each "O" to "X"
    // 3. set each "#" back to "O"
    void solve(std::vector<std::vector<char>>& board)
    {
        const int m = board.size();
        const int n = board[0].size();
        for (int row = 0; row < m; ++row) {
            for (int col = 0; col < n; ++col) {
                if (isOnBorder(row, col, m, n) && board[row][col] == 'O') {
                    dfs(board, row, col, m, n);
                }
            }
        }
        for (int row = 0; row < m; ++row) {
            for (int col = 0; col < n; ++col) {
                if (board[row][col] == '#') {
                    board[row][col] = 'O';
                } else if (board[row][col] == 'O') {
                    board[row][col] = 'X';
                }
            }
        }
    }

private:
    inline bool isOnBorder(int row, int col, int m, int n)
    {
        return row == 0 || row == m - 1 || col == 0 || col == n - 1;
    }

    void dfs(std::vector<std::vector<char>>& board, int row, int col, int m, int n)
    {
        // row in range [0, m), col in range [0, n)
        if (row < 0 || row >= m || col < 0 || col >= n)
            return;

        // board[row][col] == '#' means the current position is already processed
        if (board[row][col] == 'X' || board[row][col] == '#')
            return;

        board[row][col] = '#';
        dfs(board, row - 1, col, m, n); // up
        dfs(board, row + 1, col, m, n); // bottom
        dfs(board, row, col - 1, m, n); // left
        dfs(board, row, col + 1, m, n); // right
    }
};