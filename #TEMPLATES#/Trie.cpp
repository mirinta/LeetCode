#include <array>
#include <string>
#include <vector>

/**
 * @note The following implementation considers only lowercase English letters.
 *
 * @note The following implementation does not consider resource management.
 */
class Trie
{
    struct TrieNode;

public:
    explicit Trie() : root(new TrieNode()) {}

    void insert(const std::string& word);

    void erase(const std::string& word);

    int countWordsEqualTo(const std::string& word);

    int countWordsStartingWith(const std::string& prefix);

    std::string shortestCommonPrefix();

    std::string longestCommonPrefix();

    std::vector<std::string> findWordsWithPrefix(const std::string& prefix);

private:
    struct TrieNode
    {
        static constexpr int R = 26;
        int countWord{0};
        int countPass{0};
        std::array<TrieNode*, R> next{};
    };

    TrieNode* root;
};