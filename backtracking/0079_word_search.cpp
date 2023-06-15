#include <string>
#include <vector>

/**
 * Given an m x n grid of characters "board" and a string "word", return true if "word" exists in
 * the grid.
 *
 * The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are
 * horizontally or vertically neighboring. The same letter cell may not be used more than once.
 *
 * ! m == board.length
 * ! n = board[i].length
 * ! 1 <= m, n <= 6
 * ! 1 <= word.length <= 15
 * ! board and word consists of only lowercase and uppercase English letters.
 */

class Solution
{
public:
    bool exist(const std::vector<std::vector<char>>& board, std::string word)
    {
        if (board.empty())
            return false;

        const auto m = board.size();
        const auto n = board[0].size();
        found = false;
        visited.clear();
        visited.resize(m, std::vector<bool>(n, false));
        for (size_t x = 0; x < m; ++x) {
            for (size_t y = 0; y < n; ++y) {
                backtrack(x, y, 0, board, word);
                if (found)
                    return true;
            }
        }
        return false;
    }

private:
    bool found = false;
    std::vector<std::vector<bool>> visited;

    void backtrack(int x, int y, int i, const std::vector<std::vector<char>>& board,
                   const std::string& word)
    {
        if (i == word.size()) {
            found = true;
            return;
        }

        if (found || x < 0 || x >= board.size() || y < 0 || y >= board[0].size())
            return;

        if (visited[x][y] || word[i] != board[x][y])
            return;

        visited[x][y] = true;
        backtrack(x - 1, y, i + 1, board, word);
        backtrack(x + 1, y, i + 1, board, word);
        backtrack(x, y - 1, i + 1, board, word);
        backtrack(x, y + 1, i + 1, board, word);
        visited[x][y] = false;
    }
};