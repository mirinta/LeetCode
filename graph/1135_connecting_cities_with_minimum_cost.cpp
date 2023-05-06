#include <algorithm>
#include <vector>

/**
 * There are "n" cities labeled from 1 to n.
 *
 * You are given the integer n and an array "connections" where connections[i] = [x_i, y_i, cost_i]
 * indicates that the cost of connecting city x_i and city y_i (bidirectional connection) is cost_i.
 *
 * Return the minimum cost to connect all the n cities such that there is at least one path between
 * each pair of cities. If it is impossible to connect all the n cities, return -1.
 *
 * The cost is the sum of the connection's costs used.
 *
 * ! connections[i].length == 3
 * ! 1 <= xi, yi <= n
 * ! xi != yi
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

    int find(int x) const
    {
        if (m_parent[x] != x) {
            m_parent[x] = find(m_parent[x]);
        }
        return m_parent[x];
    }

    bool connect(int p, int q)
    {
        const auto rootP = find(p);
        const auto rootQ = find(q);
        if (rootP == rootQ)
            // already connected, if still do so, it will make a cycle
            return false;

        m_parent[rootQ] = rootP;
        m_count--;
        return true;
    }

private:
    mutable std::vector<int> m_parent;
    int m_count;
};

class Solution
{
public:
    // version 1: Minimum Spanning Tree, Kruskal Algorithm
    // - sort the edges in ascending order, initialize an empty tree T;
    // - for each edge E, skip E if adding it to T causes a cycle, otherwise add it to T;
    // - stop the loop if T has N - 1 edges, where N is the number of nodes.
    int minimumCost(int n, std::vector<std::vector<int>>& connections)
    {
        UnionFind uf(n);
        int result = 0;
        using Edge = std::vector<int>;
        std::sort(connections.begin(), connections.end(),
                  [](const Edge& edge1, const Edge& edge2) { return edge1[2] < edge2[2]; });
        for (const auto& edge : connections) {
            // x_i and y_i are 1-indexed
            if (!uf.connect(edge[0] - 1, edge[1] - 1))
                continue;

            result += edge[2];
        }
        return uf.count() == 1 ? result : -1;
    }
};