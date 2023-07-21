#include <algorithm>
#include <array>
#include <memory>
#include <string>

struct TrieNode
{
    static constexpr int R = 26;
    int countPass = 0; // num of words that pass through this character
    int countWord = 0; // num of words that end with this character
    std::array<std::unique_ptr<TrieNode>, 26> next;
};

class Trie
{
public:
    Trie() : root(std::make_unique<TrieNode>()) {}

    void insert(const std::string& word)
    {
        auto* node = root.get();
        for (const auto& c : word) {
            const int index = c - 'a';
            if (!node->next[index]) {
                node->next[index] = std::make_unique<TrieNode>();
            }
            node->next[index]->countPass++;
            node = node->next[index].get();
        }
        node->countWord++;
    }

    int countWordsEqualTo(const std::string& word)
    {
        auto* node = root.get();
        for (const auto& c : word) {
            const int index = c - 'a';
            if (!node->next[index])
                return 0;

            node = node->next[index].get();
        }
        return node->countWord;
    }

    int countWordsStartingWith(const std::string& prefix)
    {
        auto* node = root.get();
        for (const auto& c : prefix) {
            const int index = c - 'a';
            if (!node->next[index])
                return 0;

            node = node->next[index].get();
        }
        return node->countPass;
    }

    void erase(const std::string& word)
    {
        auto* node = root.get();
        for (const auto& c : word) {
            const int index = c - 'a';
            if (node->next[index] && --node->next[index]->countPass == 0) {
                node->next[index].reset();
                return;
            }
            node = node->next[index].get();
        }
        node->countWord--;
    }

private:
    std::unique_ptr<TrieNode> root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */