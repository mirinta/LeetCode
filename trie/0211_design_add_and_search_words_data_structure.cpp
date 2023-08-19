#include <array>
#include <string>
#include <vector>

struct TrieNode
{
    static constexpr int R = 26;
    std::array<TrieNode*, R> next{nullptr};
    bool isEnd = false;
};

class WordDictionary
{
public:
    WordDictionary() : root(new TrieNode()) {}

    void addWord(const std::string& word)
    {
        auto* node = root;
        for (const auto& c : word) {
            const int index = c - 'a';
            if (!node->next[index]) {
                node->next[index] = new TrieNode();
            }
            node = node->next[index];
        }
        node->isEnd = true;
    }

    bool search(const std::string& word) { return dfs(root, 0, word); }

private:
    bool dfs(TrieNode* node, int idx, const std::string& word)
    {
        if (idx == word.size())
            return node->isEnd;

        if (word[idx] != '.')
            return node->next[word[idx] - 'a'] ? dfs(node->next[word[idx] - 'a'], idx + 1, word)
                                               : false;

        for (auto* nextNode : node->next) {
            if (nextNode && dfs(nextNode, idx + 1, word))
                return true;
        }
        return false;
    }

private:
    TrieNode* root;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */