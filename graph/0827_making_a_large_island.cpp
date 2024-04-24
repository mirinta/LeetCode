#include <unordered_set>
#include <vector>

/**
 * You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
 *
 * Return the size of the largest island in grid after applying this operation.
 *
 * An island is a 4-directionally connected group of 1s.
 *
 * ! n == grid.length
 * ! n == grid[i].length
 * ! 1 <= n <= 500
 * ! grid[i][j] is either 0 or 1.
 */

class UnionFind
{
public:
    explicit UnionFind(int n) : root(n), rank(n, 1)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
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
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (rank[rootQ] > rank[rootP]) {
            std::swap(rootP, rootQ);
        }
        root[rootQ] = rootP;
        rank[rootP] += rank[rootQ];
    }

    int area(int x) { return rank[find(x)]; }

private:
    std::vector<int> root;
    std::vector<int> rank;
};

class Solution
{
public:
    int largestIsland(std::vector<std::vector<int>>& grid)
    {
        static const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        const int m = grid.size();
        const int n = grid[0].size();
        UnionFind uf(m * n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != 1)
                    continue;

                for (const auto& [dx, dy] : kDirections) {
                    const int x = i + dx;
                    const int y = j + dy;
                    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != 1)
                        continue;

                    uf.connect(encode(i, j, n), encode(x, y, n));
                }
            }
        }
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    result = std::max(result, uf.area(encode(i, j, n)));
                    continue;
                }
                std::unordered_set<int> parents;
                int area = 1;
                for (const auto& [dx, dy] : kDirections) {
                    const int x = i + dx;
                    const int y = j + dy;
                    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != 1)
                        continue;

                    const int p = uf.find(encode(x, y, n));
                    if (parents.insert(p).second) {
                        area += uf.area(p);
                    }
                }
                result = std::max(result, area);
            }
        }
        return result;
    }

private:
    int encode(int i, int j, int n) { return i * n + j; }
};