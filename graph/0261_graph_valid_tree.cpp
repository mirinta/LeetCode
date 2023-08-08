#include <vector>

/**
 * You have a graph of "n" nodes labeled from 0 to n - 1.
 *
 * You are given an integer n and a list of "edges" where edges[i] = [ai, bi] indicates that there
 * is an undirected edge between nodes ai and bi in the graph.
 *
 * Return true if the edges of the given graph make up a valid tree, and false otherwise.
 *
 * ! 1 <= n <= 2000
 * ! 0 <= edges.length <= 5000
 * ! edges[i].length == 2
 * ! 0 <= ai, bi < n
 * ! ai != bi
 * ! There are no self-loops or repeated edges.
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

    int numOfConnectedComponents() const { return count; };

    int find(int x)
    {
        if (root[x] != x) {
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
    // time O(E*a(N)), space O(N)
    bool validTree(int n, std::vector<std::vector<int>>& edges)
    {
        UnionFind uf(n);
        for (const auto& edge : edges) {
            const auto& p = edge[0];
            const auto& q = edge[1];
            if (uf.isConnected(p, q))
                return false;

            uf.connect(p, q);
        }
        return uf.numOfConnectedComponents() == 1;
    }
};
