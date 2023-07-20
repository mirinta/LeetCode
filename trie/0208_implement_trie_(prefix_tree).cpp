#include <array>
#include <memory>
#include <string>

/**
 * A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store
 * and retrieve keys in a dataset of strings. There are various applications of this data structure,
 * such as autocomplete and spellchecker.
 *
 * Implement the Trie class:
 *
 * - Trie() Initializes the trie object.
 *
 * - void insert(String word) Inserts the string word into the trie.
 *
 * - boolean search(String word) Returns true if the string word is in the trie (i.e., was inserted
 * before), and false otherwise.
 *
 * - boolean startsWith(String prefix) Returns true if there is a previously inserted string word
 * that has the prefix prefix, and false otherwise.
 *
 * ! 1 <= word.length, prefix.length <= 2000
 * ! word and prefix consist only of lowercase English letters.
 * ! At most 3 * 10^4 calls in total will be made to insert, search, and startsWith.
 */

struct TrieNode
{
    static constexpr int R = 26;
    bool isEnd = false;
    std::array<std::unique_ptr<TrieNode>, R> next;
};

class Trie
{
public:
    explicit Trie() : root(std::make_unique<TrieNode>()) {}

    void insert(const std::string& word)
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

    bool search(const std::string& word)
    {
        auto* node = root.get();
        for (const auto& c : word) {
            const int index = c - 'a';
            if (!node->next[index])
                return false;

            node = node->next[index].get();
        }
        return node->isEnd;
    }

    bool startsWith(const std::string& prefix)
    {
        auto* node = root.get();
        for (const auto& c : prefix) {
            const int index = c - 'a';
            if (!node->next[index])
                return false;

            node = node->next[index].get();
        }
        return true;
    }

private:
    std::unique_ptr<TrieNode> root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */