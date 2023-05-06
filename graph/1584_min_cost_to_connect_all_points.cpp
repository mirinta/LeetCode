#include <algorithm>
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
    explicit UnionFind(int n) : m_parent(n, 0), m_count(n)
    {
        for (size_t i = 0; i < n; ++i) {
            m_parent[i] = i;
        }
    }

    int count() const { return m_count; }

    bool connect(int p, int q)
    {
        const auto rootP = find(p);
        const auto rootQ = find(q);
        if (rootP == rootQ)
            return false;

        m_parent[rootQ] = rootP;
        m_count--;
        return true;
    }

    int find(int x) const
    {
        if (x != m_parent[x]) {
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
    int minCostConnectPoints(const std::vector<std::vector<int>>& points)
    {
        // build edges
        using Edge = std::vector<int>; // node1, node2, cost
        std::vector<Edge> edges;
        for (int i = 0; i < points.size(); ++i) {
            for (int j = i + 1; j < points.size(); ++j) {
                const auto& point1 = points[i];
                const auto& point2 = points[j];
                const auto cost = std::abs(point1[0] - point2[0]) + std::abs(point1[1] - point2[1]);
                edges.push_back({i, j, cost});
            }
        }
        // sort edges
        std::sort(edges.begin(), edges.end(),
                  [](const Edge& e1, const Edge& e2) { return e1[2] < e2[2]; });
        // MST: Kruskal algorithm
        UnionFind uf(points.size()); // not edges.size()
        int result = 0;
        for (const auto& edge : edges) {
            if (!uf.connect(edge[0], edge[1]))
                continue;

            result += edge[2];
        }
        return uf.count() == 1 ? result : 0;
    }
};
