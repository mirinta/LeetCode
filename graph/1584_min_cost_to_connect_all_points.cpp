#include <algorithm>
#include <queue>
#include <vector>

/**
 * You are given an array "points" representing integer coordinates of some points on a 2D-plane,
 * where points[i] = [xi, yi].
 *
 * The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them:
 * |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.
 *
 * Return the minimum cost to make all points connected. All points are connected if there is
 * exactly one simple path between any two points.
 *
 * ! 1 <= points.length <= 1000
 * ! -10^6 <= xi, yi <= 10^6
 * ! All pairs (xi, yi) are distinct.
 */

class UnionFind
{
public:
    explicit UnionFind(int n) : count(n), root(n), rank(n)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
            rank[i] = 1;
        }
    }

    int numOfConnectedComponents() const { return count; }

    int find(int x)
    {
        if (x != root[x]) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    bool isConnected(int p, int q) { return find(p) == find(q); }

    void connect(int p, int q)
    {
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (rank[rootP] > rank[rootQ]) {
            root[rootQ] = rootP;
        } else if (rank[rootP] < rank[rootQ]) {
            root[rootP] = rootQ;
        } else {
            root[rootQ] = rootP;
            rank[rootP]++;
        }
        count--;
    }

private:
    int count;
    std::vector<int> root;
    std::vector<int> rank;
};

class Solution
{
public:
    int minCostConnectPoints(std::vector<std::vector<int>>& points) { return approach2(points); }

private:
    int manhattanDistance(const std::vector<int>& p1, const std::vector<int>& p2)
    {
        return std::abs(p1[0] - p2[0]) + std::abs(p1[1] - p2[1]);
    }

    // Prim's algorithm
    int approach2(std::vector<std::vector<int>>& points)
    {
        const int n = points.size();
        using Pair = std::pair<int, int>; // <cost, vertex>
        auto comparator = [](const auto& p1, const auto& p2) { return p1.first > p2.first; };
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(
            comparator); // min heap
        for (int i = 1; i < n; ++i) {
            pq.push({manhattanDistance(points[0], points[i]), i});
        }
        std::vector<bool> visited(n, false);
        visited[0] = true;
        int result = 0;
        int edges = 0;
        while (!pq.empty()) {
            const auto [cost, v] = pq.top();
            pq.pop();
            if (visited[v])
                continue;

            visited[v] = true;
            result += cost;
            edges++;
            for (int i = 0; i < n; ++i) {
                if (!visited[i]) {
                    pq.push({manhattanDistance(points[v], points[i]), i});
                }
            }
        }
        return edges == n - 1 ? result : -1;
    }

    // Kruskal's algorithm
    int approach1(std::vector<std::vector<int>>& points)
    {
        const int n = points.size();
        std::vector<std::tuple<int, int, int>> edges; // <cost, x, y>
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                edges.push_back({manhattanDistance(points[i], points[j]), i, j});
            }
        }
        std::sort(edges.begin(), edges.end(),
                  [](const auto& e1, const auto& e2) { return std::get<0>(e1) < std::get<0>(e2); });
        UnionFind uf(n);
        int result = 0;
        for (const auto& edge : edges) {
            const auto& cost = std::get<0>(edge);
            const auto& from = std::get<1>(edge);
            const auto& to = std::get<2>(edge);
            if (!uf.isConnected(from, to)) {
                result += cost;
                uf.connect(from, to);
            }
        }
        return uf.numOfConnectedComponents() == 1 ? result : -1;
    }
};
