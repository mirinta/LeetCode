#include <vector>

/**
 * There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1
 * (inclusive). The edges in the graph are represented as a 2D integer array edges, where each
 * edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi. Every vertex
 * pair is connected by at most one edge, and no vertex has an edge to itself.
 *
 * You want to determine if there is a valid path that exists from vertex source to vertex
 * destination.
 *
 * Given edges and the integers n, source, and destination, return true if there is a valid path
 * from source to destination, or false otherwise.
 *
 * ! 1 <= n <= 2 * 10^5
 * ! 0 <= edges.length <= 2 * 10^5
 * ! edges[i].length == 2
 * ! 0 <= ui, vi <= n - 1
 * ! ui != vi
 * ! 0 <= source, destination <= n - 1
 * ! There are no duplicate edges.
 * ! There are no self edges.
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

    int isConnected(int p, int q) { return find(p) == find(q); }

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
    bool validPath(int n, std::vector<std::vector<int>>& edges, int source, int destination)
    {
        return approach2(n, edges, source, destination);
    }

private:
    bool approach1(int n, std::vector<std::vector<int>>& edges, int source, int destination)
    {
        UnionFind uf(n);
        for (const auto& edge : edges) {
            uf.connect(edge[0], edge[1]);
        }
        return uf.isConnected(source, destination);
    }

    bool approach2(int n, std::vector<std::vector<int>>& edges, int source, int destination)
    {
        std::vector<std::vector<int>> graph(n, std::vector<int>{});
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        std::vector<bool> visited(n, false);
        return dfs(visited, source, destination, graph);
    }

    bool dfs(std::vector<bool>& visited, int source, int destination,
             const std::vector<std::vector<int>>& graph)
    {
        if (source == destination)
            return true;

        visited[source] = true;
        for (const auto& adj : graph[source]) {
            if (visited[adj])
                continue;

            if (dfs(visited, adj, destination, graph))
                return true;
        }
        return false;
    }
};