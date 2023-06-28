#include <vector>

/**
 * You have a graph of "n" nodes labeled from 0 to n - 1.
 *
 * You are given an integer n and a list of "edges" where edges[i] = [ai, bi] indicates that there
 * is an undirected edge between nodes ai and bi in the graph.
 *
 * Return true if the edges of the given graph make up a valid tree, and false otherwise.
 *
 * ! edges[i].length == 2
 * ! 0 <= ai, bi < n
 * ! ai != bi
 * ! There are no self-loops or repeated edges.
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

    bool isConnected(int p, int q) { return find(p) == find(q); }

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
    bool validTree(int n, std::vector<std::vector<int>>& edges)
    {
        // a valid tree:
        // - no cycle
        // - all nodes are connected, i.e., uf.count() = 1
        UnionFind uf(n);
        for (const auto& edge : edges) {
            const int& p = edge[0];
            const int& q = edge[1];
            if (uf.isConnected(p, q))
                return false;

            uf.connect(p, q);
        }
        return uf.count() == 1;
    }
};
