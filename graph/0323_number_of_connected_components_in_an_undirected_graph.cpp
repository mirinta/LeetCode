#include <vector>

/**
 * You have a graph of "n" nodes. You are given an integer "n" and an array "edges" where edges[i] =
 * [ai, bi] indicates that there is an edge between ai and bi in the graph.
 *
 * Return the number of connected components in the graph.
 */

class UnionFind
{
public:
    explicit UnionFind(int n) : _root(n), _rank(n), _count(n)
    {
        for (int i = 0; i < n; ++i) {
            _root[i] = i;
            _rank[i] = 1;
        }
    }

    int count() const { return _count; }

    int find(int x)
    {
        if (x != _root[x]) {
            _root[x] = find(_root[x]);
        }
        return _root[x];
    }

    void connect(int p, int q)
    {
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (_rank[rootP] > _rank[rootQ]) {
            _root[rootQ] = rootP;
        } else if (_rank[rootP] < _rank[rootQ]) {
            _root[rootP] = rootQ;
        } else {
            _root[rootQ] = rootP;
            _rank[rootP] += 1;
        }
        _count -= 1;
    }

private:
    std::vector<int> _root;
    std::vector<int> _rank;
    int _count;
};

class Solution
{
public:
    int countComponents(int n, std::vector<std::vector<int>>& edges)
    {
        UnionFind uf(n);
        for (const auto& edge : edges) {
            const int& p = edge[0];
            const int& q = edge[1];
            uf.connect(p, q);
        }
        return uf.count();
    }
};
