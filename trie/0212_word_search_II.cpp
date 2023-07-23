#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given an m x n board of characters and a list of strings words, return all words on the board.
 *
 * Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells
 * are horizontally or vertically neighboring. The same letter cell may not be used more than once
 * in a word.
 *
 * ! m == board.length
 * ! n == board[i].length
 * ! 1 <= m, n <= 12
 * ! board[i][j] is a lowercase English letter.
 * ! 1 <= words.length <= 3 * 10^4
 * ! 1 <= words[i].length <= 10
 * ! words[i] consists of lowercase English letters.
 * ! All the strings of words are unique.
 */

struct TrieNode
{
    std::unordered_map<char, TrieNode*> next;
    std::string word{};
};

class Solution
{
public:
    std::vector<std::string> findWords(std::vector<std::vector<char>>& board,
                                       std::vector<std::string>& words)
    {
        root = new TrieNode();
        for (const auto& word : words) {
            auto* node = root;
            for (const auto& c : word) {
                if (!node->next.count(c)) {
                    node->next[c] = new TrieNode();
                }
                node = node->next[c];
            }
            node->word = word;
        }
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (root->next.count(board[i][j])) {
                    backtrack(i, j, root, board);
                }
            }
        }
        return result;
    }

private:
    void backtrack(int i, int j, TrieNode* parent, std::vector<std::vector<char>>& board)
    {
        const char c = board[i][j];
        if (!parent || !parent->next.count(c))
            return;

        auto* node = parent->next[c];
        if (!node->word.empty()) {
            result.push_back(node->word);
            node->word.clear();
        }
        const int m = board.size();
        const int n = board[0].size();
        board[i][j] = '#';
        for (const auto& [dx, dy] : kDirections) {
            const int x = i + dx;
            const int y = j + dy;
            if (x < 0 || x >= m || y < 0 || y >= n)
                continue;

            if (node->next.count(board[x][y])) {
                backtrack(x, y, node, board);
            }
        }
        board[i][j] = c;
        if (node->next.empty()) {
            parent->next.erase(c);
        }
    }

private:
    TrieNode* root;
    std::vector<std::string> result;
    const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
};