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
    explicit UnionFind(int n) : m_parent(n, 0), m_count(n)
    {
        for (size_t i = 0; i < n; ++i) {
            m_parent[i] = i;
        }
    }

    int count() const { return m_count; }

    bool isConnected(int p, int q) const
    {
        const auto rootP = find(p);
        const auto rootQ = find(q);
        return rootP == rootQ;
    }

    void connect(int p, int q)
    {
        const auto rootP = find(p);
        const auto rootQ = find(q);
        if (rootP == rootQ)
            return;

        m_parent[rootP] = rootQ;
        m_count--;
    }

    int find(int x) const
    {
        if (m_parent[x] != x) {
            m_parent[x] = find(m_parent[x]);
        }
        return m_parent[x];
    }

private:
    mutable std::vector<int> m_parent;
    int m_count;
};

class Solution
{
public:
    int countComponents(int n, std::vector<std::vector<int>>& edges)
    {
        UnionFind uf(n);
        for (const auto& edge : edges) {
            uf.connect(edge[0], edge[1]);
        }
        return uf.count();
    }
};