#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Design a search autocomplete system for a search engine. Users may input a sentence (at least one
 * word and end with a special character '#').
 *
 * You are given a string array sentences and an integer array times both of length n where
 * sentences[i] is a previously typed sentence and times[i] is the corresponding number of times the
 * sentence was typed. For each input character except '#', return the top 3 historical hot
 * sentences that have the same prefix as the part of the sentence already typed.
 *
 * Here are the specific rules:
 *
 * - The hot degree for a sentence is defined as the number of times a user typed the exactly same
 * sentence before.
 *
 * - The returned top 3 hot sentences should be sorted by hot degree (The first is the hottest one).
 * If several sentences have the same hot degree, use ASCII-code order (smaller one appears first).
 *
 * - If less than 3 hot sentences exist, return as many as you can.
 *
 * - When the input is a special character, it means the sentence ends, and in this case, you need
 * to return an empty list.
 *
 * Implement the AutocompleteSystem class:
 *
 * - AutocompleteSystem(String[] sentences, int[] times) Initializes the object with the sentences
 * and times arrays.
 *
 * - List<String> input(char c) This indicates that the user typed the character c.
 *
 * -- Returns an empty array [] if c == '#' and stores the inputted sentence in the system.
 *
 * -- Returns the top 3 historical hot sentences that have the same prefix as the part of the
 * sentence already typed. If there are fewer than 3 matches, return them all.
 *
 * ! n == sentences.length
 * ! n == times.length
 * ! 1 <= n <= 100
 * ! 1 <= sentences[i].length <= 100
 * ! 1 <= times[i] <= 50
 * ! c is a lowercase English letter, a hash '#', or space ' '.
 * ! Each tested sentence will be a sequence of characters c that end with the character '#'.
 * ! Each tested sentence will have a length in the range [1, 200].
 * ! The words in each input sentence are separated by single spaces.
 * ! At most 5000 calls will be made to input.
 */

struct TrieNode
{
    int count = 0;
    std::unordered_map<char, std::unique_ptr<TrieNode>> next;
};

class Trie
{
public:
    explicit Trie() : root(std::make_unique<TrieNode>()) {}

    void insert(const std::string& sentence, int times)
    {
        if (sentence.empty() || times < 1)
            return;

        auto* node = root.get();
        for (const auto& c : sentence) {
            if (!node->next.count(c)) {
                node->next[c] = std::make_unique<TrieNode>();
            }
            node = node->next[c].get();
        }
        node->count += times;
    }

    std::vector<std::string> getSentencesWithPrefix(const std::string& prefix, size_t numLimit)
    {
        auto* node = root.get();
        std::string sentence;
        for (const auto& c : prefix) {
            if (!node->next.count(c))
                return {};

            sentence.push_back(c);
            node = node->next[c].get();
        }
        std::vector<std::pair<std::string, int>> sentences;
        dfs(sentences, sentence, node);
        std::sort(sentences.begin(), sentences.end(), [](const auto& p1, const auto& p2) {
            return p1.second == p2.second ? p1.first < p2.first : p1.second > p2.second;
        });
        std::vector<std::string> result(std::min(sentences.size(), numLimit));
        for (int i = 0; i < result.size(); ++i) {
            result[i] = sentences[i].first;
        }
        return result;
    }

private:
    void dfs(std::vector<std::pair<std::string, int>>& sentences, std::string& sentence,
             TrieNode* node)
    {
        if (!node)
            return;

        if (node->count > 0) {
            sentences.push_back({sentence, node->count});
        }
        for (const auto& [c, ptr] : node->next) {
            if (node->next[c]) {
                sentence.push_back(c);
                dfs(sentences, sentence, ptr.get());
                sentence.pop_back();
            }
        }
    }

private:
    std::unique_ptr<TrieNode> root;
};

class AutocompleteSystem
{
public:
    AutocompleteSystem(std::vector<std::string>& sentences, std::vector<int>& times)
    {
        for (int i = 0; i < sentences.size(); ++i) {
            trie.insert(sentences[i], times[i]);
        }
    }

    std::vector<std::string> input(char c)
    {
        if (c == '#') {
            trie.insert(prefix, 1);
            prefix.clear();
            return {};
        }
        prefix.push_back(c);
        return trie.getSentencesWithPrefix(prefix, 3);
    }

private:
    std::string prefix;
    Trie trie;
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */