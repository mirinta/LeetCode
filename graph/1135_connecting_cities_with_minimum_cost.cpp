#include <algorithm>
#include <queue>
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
    // approach 1: Minimum Spanning Tree, Kruskal's algorithm
    // - sort the edges in ascending order, initialize an empty tree T;
    // - for each edge E, skip E if adding it to T causes a cycle, otherwise add it to T;
    // - stop the loop if T has N - 1 edges, where N is the number of nodes.
    // int minimumCost(int n, vector<vector<int>>& connections) {
    //     UnionFind uf(n);
    //     int result = 0;
    //     using Edge = std::vector<int>;
    //     std::sort(connections.begin(), connections.end(),
    //               [](const Edge& edge1, const Edge& edge2) { return edge1[2] < edge2[2]; });
    //     for (const auto& edge : connections) {
    //         // x_i and y_i are 1-indexed
    //         if (!uf.connect(edge[0] - 1, edge[1] - 1))
    //             continue;

    //         result += edge[2];
    //     }
    //     return uf.count() == 1 ? result : -1;
    // }
    // approach 2: MST, Prim's algorithm
    int minimumCost(int n, std::vector<std::vector<int>>& connections)
    {
        if (connections.empty())
            return -1;

        // build graph and other initializations
        graph = std::vector<std::vector<Edge>>(n, std::vector<Edge>{});
        for (const auto& edge : connections) {
            const auto from = edge[0] - 1; // 1-indexed
            const auto to = edge[1] - 1;   // 1-indexed
            const auto weight = edge[2];
            graph[from].push_back({from, to, weight});
            graph[to].push_back({to, from, weight});
        }
        visited = std::vector<bool>(n, false);
        result = 0;
        // start with node 0
        cut(0);
        while (!minHeap.empty()) {
            const auto edge = minHeap.top();
            minHeap.pop();
            const auto to = edge[1];
            if (visited[to])
                continue;

            result += edge[2];
            cut(to);
        }
        // check if all nodes are visited
        for (const auto& flag : visited) {
            if (!flag)
                return -1;
        }
        return result;
    }

private:
    using Edge = std::vector<int>;        // [from, to, weight]
    std::vector<std::vector<Edge>> graph; // indirected graph
    int result = 0;
    std::vector<bool> visited;
    static constexpr auto comp = [](const Edge& e1, const Edge& e2) -> bool {
        return e1[2] > e2[2];
    };
    std::priority_queue<Edge, std::vector<Edge>, decltype(comp)> minHeap{comp};

    void cut(int from)
    {
        visited[from] = true;
        for (const auto& edge : graph[from]) {
            if (!visited[edge[1]]) {
                minHeap.push(edge);
            }
        }
    }
};