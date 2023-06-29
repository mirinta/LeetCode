#include <queue>
#include <vector>

/**
 * There are n houses in a village. We want to supply water for all the houses by building wells and
 * laying pipes.
 *
 * For each house i, we can either build a well inside it directly with cost wells[i - 1] (note the
 * -1 due to 0-indexing), or pipe in water from another well to it. The costs to lay pipes between
 * houses are given by the array pipes where each pipes[j] = [house1j, house2j, costj] represents
 * the cost to connect house1j and house2j together using a pipe. Connections are bidirectional, and
 * there could be multiple valid connections between the same two houses with different costs.
 *
 * Return the minimum total cost to supply water to all houses.
 *
 * ! 2 <= n <= 10^4
 * ! wells.length == n
 * ! 0 <= wells[i] <= 10^5
 * ! 1 <= pipes.length <= 10^4
 * ! pipes[j].length == 3
 * ! 1 <= house1j, house2j <= n
 * ! 0 <= costj <= 10^5
 * ! house1j != house2j
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
        int rootP = find(p);
        int rootQ = find(q);
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
    int minCostToSupplyWater(int n, std::vector<int>& wells, std::vector<std::vector<int>>& pipes)
    {
        return approach2(n, wells, pipes);
    }

private:
    // Kruskal's MST algorithm
    int approach1(int n, std::vector<int>& wells, std::vector<std::vector<int>>& pipes)
    {
        // a virtual source node, id = 0
        for (int i = 0; i < n; ++i) {
            pipes.push_back({0, i + 1, wells[i]}); // maintain 1-indexed
        }
        std::sort(pipes.begin(), pipes.end(),
                  [](const auto& pipe1, const auto& pipe2) { return pipe1[2] < pipe2[2]; });
        UnionFind uf(n + 1);
        int result = 0;
        for (const auto& pipe : pipes) {
            const int& p = pipe[0];
            const int& q = pipe[1];
            if (uf.isConnected(p, q))
                continue;

            uf.connect(p, q);
            result += pipe[2];
        }
        return result;
    }

    // Prim's MST algorithm
    int approach2(int n, std::vector<int>& wells, std::vector<std::vector<int>>& pipes)
    {
        std::vector<std::vector<std::pair<int, int>>> graph(n + 1,
                                                            std::vector<std::pair<int, int>>{});
        for (int i = 1; i <= n; ++i) {
            graph[0].push_back({-1 * wells[i - 1], i});
            graph[i].push_back({-1 * wells[i - 1], 0});
        }
        for (const auto& pipe : pipes) {
            graph[pipe[0]].push_back({-1 * pipe[2], pipe[1]});
            graph[pipe[1]].push_back({-1 * pipe[2], pipe[0]});
        }
        std::priority_queue<std::pair<int, int>> pq;
        std::vector<bool> visited(n + 1, false);
        visited[0] = true;
        cut(visited, pq, 0, graph);
        int result = 0;
        while (!pq.empty()) {
            const auto [negativeCost, v] = pq.top();
            pq.pop();
            if (visited[v])
                continue;

            visited[v] = true;
            result += -1 * negativeCost;
            cut(visited, pq, v, graph);
        }
        return result;
    }

    void cut(std::vector<bool>& visited, std::priority_queue<std::pair<int, int>>& pq, int v,
             const std::vector<std::vector<std::pair<int, int>>>& graph)
    {
        for (const auto& pair : graph[v]) {
            if (visited[pair.second])
                continue;

            pq.push(pair);
        }
    }
};