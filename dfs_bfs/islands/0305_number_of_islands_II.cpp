#include <unordered_set>
#include <vector>

/**
 * You are given an empty 2D binary grid grid of size m x n. The grid represents a map where 0's
 * represent water and 1's represent land. Initially, all the cells of grid are water cells (i.e.,
 * all the cells are 0's).
 *
 * We may perform an add land operation which turns the water at position into a land. You are given
 * an array positions where positions[i] = [ri, ci] is the position (ri, ci) at which we should
 * operate the ith operation.
 *
 * Return an array of integers answer where answer[i] is the number of islands after turning the
 * cell (ri, ci) into a land.
 *
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or
 * vertically. You may assume all four edges of the grid are all surrounded by water.
 *
 * ! 1 <= m, n, positions.length <= 10^4
 * ! 1 <= m * n <= 10^4
 * ! positions[i].length == 2
 * ! 0 <= ri < m
 * ! 0 <= ci < n
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

    void connect(int p, int q)
    {
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (rank[rootP] > rank[rootQ]) {
            root[rootQ] = rootP;
        } else if (rank[rootP] < rank[rootQ]) {
            root[rootQ] = rootP;
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
    std::vector<int> numIslands2(int m, int n, std::vector<std::vector<int>>& positions)
    {
        const int totalNumOfCells = m * n;
        auto encode = [n](int i, int j) { return i * n + j; };
        std::vector<int> result(positions.size());
        std::unordered_set<int> lands;
        UnionFind uf(totalNumOfCells);
        for (int i = 0; i < positions.size(); ++i) {
            const int x = positions[i][0];
            const int y = positions[i][1];
            const int encodedXY = encode(x, y);
            for (const auto& [dx, dy] : kDirections) {
                const int p = x + dx;
                const int q = y + dy;
                if (p < 0 || p >= m || q < 0 || q >= n)
                    continue;

                if (const int encodedPQ = encode(p, q); lands.count(encodedPQ)) {
                    uf.connect(encodedXY, encodedPQ);
                }
            }
            // #num of water cells = m * n - #num of land cells
            lands.insert(encodedXY);
            result[i] = uf.numOfConnectedComponents() - (totalNumOfCells - lands.size());
        }
        return result;
    }

private:
    const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
};
