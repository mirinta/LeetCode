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
    explicit UnionFind(int n) : m_parent(n, 0), m_count(n)
    {
        for (size_t i = 0; i < n; ++i) {
            m_parent[i] = i;
        }
    }

    int count() const { return m_count; }

    int isConnected(int p, int q) const
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

        m_parent[rootQ] = rootP;
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
    bool validTree(int n, std::vector<std::vector<int>>& edges)
    {
        // a valid tree:
        // - there's no cycle in it, and
        // - all nodes are connected
        UnionFind uf(n);
        for (const auto& edge : edges) {
            const auto p = edge[0];
            const auto q = edge[1];
            // if we connect p and q which are already connected,
            // it will make a cycle in the graph
            if (uf.isConnected(p, q))
                return false;

            uf.connect(p, q);
        }
        return uf.count() == 1; // check all nodes are connected
    }
};