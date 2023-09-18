#include <string>
#include <vector>

/**
 * You are given two strings of the same length s1 and s2 and a string baseStr.
 *
 * We say s1[i] and s2[i] are equivalent characters.
 *
 * - For example, if s1 = "abc" and s2 = "cde", then we have 'a' == 'c', 'b' == 'd', and 'c' == 'e'.
 *
 * Equivalent characters follow the usual rules of any equivalence relation:
 *
 * - Reflexivity: 'a' == 'a'.
 *
 * - Symmetry: 'a' == 'b' implies 'b' == 'a'.
 *
 * - Transitivity: 'a' == 'b' and 'b' == 'c' implies 'a' == 'c'.
 *
 * For example, given the equivalency information from s1 = "abc" and s2 = "cde", "acd" and "aab"
 * are equivalent strings of baseStr = "eed", and "aab" is the lexicographically smallest equivalent
 * string of baseStr.
 *
 * Return the lexicographically smallest equivalent string of baseStr by using the equivalency
 * information from s1 and s2.
 *
 * ! 1 <= s1.length, s2.length, baseStr <= 1000
 * ! s1.length == s2.length
 * ! s1, s2, and baseStr consist of lowercase English letters.
 */

class UnionFind
{
public:
    explicit UnionFind(int n) : count(n), root(n), rank(n)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
            rank[i] = 1;
        }
    }

    int numOfConnectedComponents() const { return count; }

    int find(int x)
    {
        if (x != root[x]) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    bool isConnected(int p, int q) { return find(p) == find(q); }

    void connect(int p, int q)
    {
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (rank[rootP] > rank[rootQ]) {
            root[rootQ] = rootP;
        } else if (rank[rootP] < rank[rootP]) {
            root[rootP] = rootQ;
        } else {
            root[rootQ] = rootP;
            rank[rootP]++;
        }
        count--;
    }

private:
    int count;
    std::vector<int> root;
    std::vector<int> rank;
};

class Solution
{
public:
    std::string smallestEquivalentString(const std::string& s1, const std::string& s2,
                                         const std::string& baseStr)
    {
        UnionFind uf(26);
        const int length = s1.size();
        for (int i = 0; i < length; ++i) {
            uf.connect(s1[i] - 'a', s2[i] - 'a');
        }
        std::string result(baseStr);
        for (auto& c : result) {
            for (int i = 0; i < 26; ++i) {
                if (uf.isConnected(c - 'a', i)) {
                    c = i + 'a';
                    break;
                }
            }
        }
        return result;
    }
};
