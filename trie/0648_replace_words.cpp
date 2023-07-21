#include <array>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

/**
 * In English, we have a concept called root, which can be followed by some other word to form
 * another longer word - let's call this word successor. For example, when the root "an" is followed
 * by the successor word "other", we can form a new word "another".
 *
 * Given a dictionary consisting of many roots and a sentence consisting of words separated by
 * spaces, replace all the successors in the sentence with the root forming it. If a successor can
 * be replaced by more than one root, replace it with the root that has the shortest length.
 *
 * Return the sentence after the replacement.
 *
 * ! 1 <= dictionary.length <= 1000
 * ! 1 <= dictionary[i].length <= 100
 * ! dictionary[i] consists of only lower-case letters.
 * ! 1 <= sentence.length <= 10^6
 * ! sentence consists of only lower-case letters and spaces.
 * ! The number of words in sentence is in the range [1, 1000]
 * ! The length of each word in sentence is in the range [1, 1000]
 * ! Every two consecutive words in sentence will be separated by exactly one space.
 * ! sentence does not have leading or trailing spaces.
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
            ;
        }
        node->isEnd = true;
    }

    std::string getShortestPrefix(const std::string& word)
    {
        std::string result;
        auto* node = root.get();
        for (const auto& c : word) {
            const int index = c - 'a';
            if (!node->next[index])
                return {};

            result.push_back(c);
            node = node->next[index].get();
            if (node->isEnd)
                return result;
        }
        return {};
    }

private:
    std::unique_ptr<TrieNode> root;
};

class Solution
{
public:
    std::string replaceWords(std::vector<std::string>& dictionary, std::string sentence)
    {
        Trie trie;
        for (const auto& word : dictionary) {
            trie.insert(word);
        }
        std::string result;
        std::string word;
        std::istringstream stream(sentence);
        while (std::getline(stream, word, ' ')) {
            const auto prefix = trie.getShortestPrefix(word);
            if (prefix.empty()) {
                result.append(word);
            } else {
                result.append(prefix);
            }
            result.push_back(' ');
        }
        result.pop_back();
        return result;
    }
};