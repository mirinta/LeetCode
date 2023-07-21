#include <array>
#include <memory>
#include <string>
#include <vector>

class WordDictionary
{
    struct TrieNode
    {
        static constexpr int R = 26;
        bool isEnd = false;
        std::array<std::unique_ptr<TrieNode>, R> next;
    };

public:
    WordDictionary() : root(std::make_unique<TrieNode>()) {}

    void addWord(const std::string& word)
    {
        auto* node = root.get();
        for (const auto& c : word) {
            const int index = c - 'a';
            if (!node->next[index]) {
                node->next[index] = std::make_unique<TrieNode>();
            }
            node = node->next[index].get();
        }
        node->isEnd = true;
    }

    bool search(const std::string& word) { return search(word, root.get()); }

private:
    bool search(const std::string& word, TrieNode* node)
    {
        for (int i = 0; i < word.size(); ++i) {
            const auto& c = word[i];
            if (c != kWildCard) {
                if (!node->next[c - 'a'])
                    return false;

                node = node->next[c - 'a'].get();
            } else {
                for (const auto& ptr : node->next) {
                    if (ptr && search(word.substr(i + 1, word.size()), ptr.get()))
                        return true;
                }
                return false;
            }
        }
        return node->isEnd;
    }

private:
    static constexpr char kWildCard = '.';
    std::unique_ptr<TrieNode> root;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */