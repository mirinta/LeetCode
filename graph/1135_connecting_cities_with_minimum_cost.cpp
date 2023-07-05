#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
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
    int minimumCost(int n, std::vector<std::vector<int>>& connections)
    {
        return approach1(n, connections);
    }

private:
    int approach2(int n, std::vector<std::vector<int>>& connections)
    {
        // MST, Prim's algorithm
        std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
        for (const auto& connection : connections) {
            graph[connection[0]].push_back({connection[2], connection[1]});
            graph[connection[1]].push_back({connection[2], connection[0]});
        }
        auto comp = [](const auto& p1, const auto& p2) -> bool { return p1.first > p2.first; };
        // cities are 1-indexed
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comp)>
            pq(comp);
        for (const auto& pair : graph[1]) {
            pq.push(pair);
        }
        std::unordered_set<int> visited;
        visited.insert(1);
        int result = 0;
        int edges = 0; // at the end, edges should be n-1
        while (!pq.empty()) {
            const auto [cost, v] = pq.top();
            pq.pop();
            if (visited.count(v))
                continue;

            visited.insert(v);
            result += cost;
            edges++;
            for (const auto& pair : graph[v]) {
                if (visited.count(pair.second))
                    continue;

                pq.push(pair);
            }
        }
        return edges == n - 1 ? result : -1;
    }

    int approach1(int n, std::vector<std::vector<int>>& connections)
    {
        // MST, Kruskal's algorithm
        std::sort(connections.begin(), connections.end(),
                  [](const auto& c1, const auto& c2) { return c1[2] < c2[2]; });
        UnionFind uf(n);
        int result = 0;
        for (const auto& connection : connections) {
            const int from = connection[0] - 1;
            const int to = connection[1] - 1;
            const int cost = connection[2];
            if (uf.isConnected(from, to))
                continue;

            uf.connect(from, to);
            result += cost;
        }
        return uf.count() == 1 ? result : -1;
    }
};
