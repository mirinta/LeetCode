#include <string>
#include <vector>

/**
 * You are given an array of strings "equations" that represent relationships between variables
 * where each string equation[i] is o length 4 and takes one of two different forms: "xi == yi" or
 * "xi != yi". Here, xi and yi are lowercase letters (not necessarily different) that represent
 * one-letter variable names.
 *
 * Return "true" if it is possible to assign integers to variable names so as to satisfy all the
 * given equations, or false otherwise.
 *
 * ! 1 <= equations.length <= 500
 * ! equations[i].length == 4
 * ! equations[i][0] is a lowercase letter.
 * ! equations[i][1] is either '=' or '!'.
 * ! equations[i][2] is '='.
 * ! equations[i][3] is a lowercase letter.
 */

class UnionFind
{
public:
    // node's value in range [0, n - 1]
    explicit UnionFind(int n) : _parent(n, 0)
    {
        for (int i = 0; i < n; ++i) {
            _parent[i] = i;
        }
    }

    // find the parent node of x
    // with path compression
    int find(int x) const
    {
        if (_parent[x] != x) {
            _parent[x] = find(_parent[x]);
        }
        return _parent[x];
    }

    // connect node p and node q
    void connect(int p, int q)
    {
        const auto rootP = find(p);
        const auto rootQ = find(q);
        if (rootP == rootQ)
            return;

        _parent[rootP] = rootQ;
    }

    // check node p is connected to node q
    bool isConnected(int p, int q) const
    {
        const auto rootP = find(p);
        const auto rootQ = find(q);
        return rootP == rootQ;
    }

private:
    mutable std::vector<int> _parent;
};

class Solution
{
public:
    bool equationsPossible(const std::vector<std::string>& equations)
    {
        if (equations.empty())
            return false;

        UnionFind uf(26); // 26 lowercase letters
        // for each equation that contains '==',
        // connect the operands
        for (const auto& s : equations) {
            if (s[1] == '=') {
                uf.connect(s[0] - 'a', s[3] - 'a');
            }
        }
        // for each equation that contains '!=',
        // if the operands are connected,
        // it means the equality is gonna broken, therefore return false
        for (const auto& s : equations) {
            if (s[1] == '!' && uf.isConnected(s[0] - 'a', s[3] - 'a'))
                return false;
        }
        return true;
    }
};