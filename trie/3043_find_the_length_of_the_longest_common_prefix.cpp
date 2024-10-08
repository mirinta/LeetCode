#include <array>
#include <string>
#include <unordered_set>

/**
 * You are given two arrays with positive integers arr1 and arr2.
 *
 * A prefix of a positive integer is an integer formed by one or more of its digits, starting from
 * its leftmost digit. For example, 123 is a prefix of the integer 12345, while 234 is not.
 *
 * A common prefix of two integers a and b is an integer c, such that c is a prefix of both a and b.
 * For example, 5655359 and 56554 have a common prefix 565 while 1223 and 43456 do not have a common
 * prefix.
 *
 * You need to find the length of the longest common prefix between all pairs of integers (x, y)
 * such that x belongs to arr1 and y belongs to arr2.
 *
 * Return the length of the longest common prefix among all pairs. If no common prefix exists among
 * them, return 0.
 *
 * ! 1 <= arr1.length, arr2.length <= 5 * 10^4
 * ! 1 <= arr1[i], arr2[i] <= 10^8
 */

class Trie
{
public:
    explicit Trie() : root(new TrieNode) {}

    void insert(const std::string& s)
    {
        auto* node = root;
        for (const auto& c : s) {
            const int index = c - '0';
            if (!node->next[index]) {
                node->next[index] = new TrieNode;
            }
            node = node->next[index];
        }
    }

    int lengthOfLongestCommonPrefix(const std::string& s)
    {
        auto* node = root;
        int count = 0;
        for (const auto& c : s) {
            const int index = c - '0';
            if (!node->next[index])
                break;

            count++;
            node = node->next[index];
        }
        return count;
    }

private:
    struct TrieNode
    {
        std::array<TrieNode*, 10> next{};
    };

    TrieNode* root;
};

class Solution
{
public:
    int longestCommonPrefix(std::vector<int>& arr1, std::vector<int>& arr2)
    {
        Trie trie;
        for (const auto& val : arr1) {
            trie.insert(std::to_string(val));
        }
        int result = 0;
        for (const auto& val : arr2) {
            result = std::max(result, trie.lengthOfLongestCommonPrefix(std::to_string(val)));
        }
        return result;
    }
};
