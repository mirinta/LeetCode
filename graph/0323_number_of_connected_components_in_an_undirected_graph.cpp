#include <vector>

/**
 * You have a graph of "n" nodes. You are given an integer "n" and an array "edges" where edges[i] =
 * [ai, bi] indicates that there is an edge between ai and bi in the graph.
 *
 * Return the number of connected components in the graph.
 *
 * ! 1 <= n <= 2000
 * ! 1 <= edges.length <= 5000
 * ! edges[i].length == 2
 * ! 0 <= ai <= bi < n
 * ! ai != bi
 * ! There are no repeated edges.
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

    int find(int x)
    {
        if (root[x] != x) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    void connect(int p, int q)
    {
        const auto rootP = find(p);
        const auto rootQ = find(q);
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

    int numOfConnectedComponents() const { return count; }

private:
    int count;
    std::vector<int> root;
    std::vector<int> rank;
};

class Solution
{
public:
    int countComponents(int n, std::vector<std::vector<int>>& edges)
    {
        UnionFind uf(n);
        for (const auto& edge : edges) {
            uf.connect(edge[0], edge[1]);
        }
        return uf.numOfConnectedComponents();
    }
};
