#include <vector>

/**
 * There is an undirected weighted graph with n vertices labeled from 0 to n - 1.
 *
 * You are given the integer n and an array edges, where edges[i] = [ui, vi, wi] indicates that
 * there is an edge between vertices ui and vi with a weight of wi.
 *
 * A walk on a graph is a sequence of vertices and edges. The walk starts and ends with a vertex,
 * and each edge connects the vertex that comes before it and the vertex that comes after it. It's
 * important to note that a walk may visit the same edge or vertex more than once.
 *
 * The cost of a walk starting at node u and ending at node v is defined as the bitwise AND of the
 * weights of the edges traversed during the walk. In other words, if the sequence of edge weights
 * encountered during the walk is w0, w1, w2, ..., wk, then the cost is calculated as w0 & w1 & w2 &
 * ... & wk, where & denotes the bitwise AND operator.
 *
 * You are also given a 2D array query, where query[i] = [si, ti]. For each query, you need to find
 * the minimum cost of the walk starting at vertex si and ending at vertex ti. If there exists no
 * such walk, the answer is -1.
 *
 * Return the array answer, where answer[i] denotes the minimum cost of a walk for query i.
 *
 * ! 1 <= n <= 10^5
 * ! 0 <= edges.length <= 10^5
 * ! edges[i].length == 3
 * ! 0 <= ui, vi <= n - 1
 * ! ui != vi
 * ! 0 <= wi <= 10^5
 * ! 1 <= query.length <= 10^5
 * ! query[i].length == 2
 * ! 0 <= si, ti <= n - 1
 */

class UnionFind
{
public:
    explicit UnionFind(int n) : root(n), rank(n, 1), cost(n, INT_MAX)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
    }

    int find(int x)
    {
        if (x != root[x]) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    bool isConnected(int p, int q) { return find(p) == find(q); }

    void connect(int p, int q, int weight)
    {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) {
            cost[rootP] &= weight;
            return;
        }
        if (rank[rootQ] > rank[rootP]) {
            std::swap(rootP, rootQ);
        }
        root[rootQ] = rootP;
        rank[rootP] += rank[rootQ];
        cost[rootP] &= cost[rootQ] & weight;
    }

    int minCost(int x) { return cost[find(x)]; }

private:
    std::vector<int> root;
    std::vector<int> rank;
    std::vector<int> cost;
};

class Solution
{
public:
    std::vector<int> minimumCost(int n, std::vector<std::vector<int>>& edges,
                                 std::vector<std::vector<int>>& query)
    {
        UnionFind uf(n);
        for (const auto& edge : edges) {
            uf.connect(edge[0], edge[1], edge[2]);
        }
        std::vector<int> result(query.size());
        for (int i = 0; i < query.size(); ++i) {
            const int s = query[i][0];
            const int t = query[i][1];
            if (s == t) {
                result[i] = 0;
            } else if (!uf.isConnected(s, t)) {
                result[i] = -1;
            } else {
                result[i] = uf.minCost(uf.find(s));
            }
        }
        return result;
    }
};