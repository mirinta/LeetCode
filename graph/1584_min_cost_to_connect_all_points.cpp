#include <algorithm>
#include <queue>
#include <unordered_set>
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
 * ! All pairs (xi, yi) are distinct.
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
    int minCostConnectPoints(std::vector<std::vector<int>>& points) { return approach1(points); }

private:
    int manhattanDistance(const std::vector<int>& p1, const std::vector<int>& p2)
    {
        return std::abs(p1[0] - p2[0]) + std::abs(p1[1] - p2[1]);
    }

    int approach2(std::vector<std::vector<int>>& points)
    {
        // MST, Prim's algorithm
        auto comp = [](const auto& p1, const auto& p2) -> bool { return p1.first > p2.first; };
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comp)>
            pq(comp);
        std::unordered_set<int> visited;
        visited.insert(0);
        for (int i = 1; i < points.size(); ++i) {
            pq.push({manhattanDistance(points[0], points[i]), i});
        }
        int result = 0;
        while (!pq.empty()) {
            const auto [dist, v] = pq.top();
            pq.pop();
            if (visited.count(v))
                continue;

            result += dist;
            visited.insert(v);
            for (int i = 0; i < points.size(); ++i) {
                if (visited.count(i))
                    continue;

                pq.push({manhattanDistance(points[v], points[i]), i});
            }
        }
        return result;
    }

    int approach1(std::vector<std::vector<int>>& points)
    {
        // MST, Kruskal's algorithm
        std::vector<std::vector<int>> edges;
        for (int i = 0; i < points.size(); ++i) {
            for (int j = i + 1; j < points.size(); ++j) {
                edges.push_back({manhattanDistance(points[i], points[j]), i, j});
            }
        }
        std::sort(edges.begin(), edges.end(),
                  [](const auto& v1, const auto& v2) { return v1[0] < v2[0]; });
        UnionFind uf(points.size());
        int result = 0;
        for (const auto& edge : edges) {
            const auto& cost = edge[0];
            const auto& i = edge[1];
            const auto& j = edge[2];
            if (!uf.isConnected(i, j)) {
                result += cost;
                uf.connect(i, j);
            }
        }
        return result;
    }
};
