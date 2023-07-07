#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * There is a new alien language that uses the English alphabet. However, the order among the
 * letters is unknown to you.
 *
 * You are given a list of strings words from the alien language's dictionary, where the strings in
 * words are sorted lexicographically by the rules of this new language.
 *
 * Return a string of the unique letters in the new alien language sorted in lexicographically
 * increasing order by the new language's rules. If there is no solution, return "". If there are
 * multiple solutions, return any of them.
 *
 * ! 1 <= words.length <= 100
 * ! 1 <= words[i].length <= 100
 * ! words[i] consists of only lowercase English letters.
 */

class Solution
{
public:
    std::string alienOrder(std::vector<std::string>& words)
    {
        std::unordered_map<char, std::vector<char>> graph;
        std::unordered_map<char, int> indegrees;
        for (const auto& word : words) {
            for (const auto& c : word) {
                indegrees[c] = 0;
                graph[c] = std::vector<char>{};
            }
        }
        for (int i = 0; i < words.size() - 1; ++i) {
            const auto& word1 = words[i];
            const auto& word2 = words[i + 1];
            // ! check word1 starts with word2
            if (word1.size() > word2.size() && word1.substr(0, word2.size()) == word2)
                return {};

            for (int j = 0; j < std::min(word1.size(), word2.size()); ++j) {
                if (word1[j] != word2[j]) {
                    graph[word1[j]].push_back(word2[j]);
                    indegrees[word2[j]]++;
                    break;
                }
            }
        }
        // topological sorting, Kahn's algorithm
        std::queue<char> queue;
        for (const auto& [letter, indegree] : indegrees) {
            if (indegree == 0) {
                queue.push(letter);
            }
        }
        std::string result;
        while (!queue.empty()) {
            const auto letter = queue.front();
            queue.pop();
            result.push_back(letter);
            for (const auto& next : graph[letter]) {
                if (--indegrees[next] == 0) {
                    queue.push(next);
                }
            }
        }
        if (result.size() != indegrees.size())
            return {};

        return result;
    }
};