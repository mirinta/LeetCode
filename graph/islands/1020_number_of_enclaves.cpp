#include <vector>

/**
 * You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land
 * cell.
 *
 * A move consists of walking from one land cell to another adjacent (4-directionally) land cell or
 * walking off the boundary of the grid.
 *
 * Return the number of land cells in grid for which we cannot walk off the boundary of the grid in
 * any number of moves.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 500
 * ! grid[i][j] is either 0 or 1.
 */

class Solution
{
public:
    int numEnclaves(std::vector<std::vector<int>>& grid) { return approach2(grid); }

private:
    static constexpr int kLand = 1;
    static constexpr int kWater = 0;
    const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    // approach2: DFS, flood all lands connected with those lands on the boundary
    int approach2(std::vector<std::vector<int>>& grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;

        const int m = grid.size();
        const int n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            if (grid[i][0] == kLand) {
                dfs(i, 0, grid);
            }
            if (grid[i][n - 1] == kLand) {
                dfs(i, n - 1, grid);
            }
        }
        for (int j = 0; j < n; ++j) {
            if (grid[0][j] == kLand) {
                dfs(0, j, grid);
            }
            if (grid[m - 1][j] == kLand) {
                dfs(m - 1, j, grid);
            }
        }
        int result = 0;
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (grid[i][j] == kLand) {
                    result++;
                }
            }
        }
        return result;
    }

    void dfs(int x, int y, std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        grid[x][y] = kWater;
        for (const auto& [dx, dy] : kDirections) {
            const int newX = x + dx;
            const int newY = y + dy;
            if (newX < 0 || newX >= m || newY < 0 || newY >= n || grid[newX][newY] != kLand)
                continue;

            dfs(newX, newY, grid);
        }
    }

    // approach1: UnionFind
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
                _rank[rootP]++;
            }
            _count--;
        }

        bool isConnected(int p, int q) { return find(p) == find(q); }

    private:
        std::vector<int> _root;
        std::vector<int> _rank;
        int _count;
    };

    int approach1(std::vector<std::vector<int>>& grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;

        const int m = grid.size();
        const int n = grid[0].size();
        UnionFind uf(m * n + 1);
        const int kVirtual = m * n; // connect with lands on the boundary
        std::vector<std::pair<int, int>> landsNotOnBoudary;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != kLand)
                    continue;

                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    uf.connect(kVirtual, i * n + j);
                } else {
                    landsNotOnBoudary.push_back({i, j});
                }
                for (const auto& [dx, dy] : kDirections) {
                    const int x = i + dx;
                    const int y = j + dy;
                    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != kLand)
                        continue;

                    uf.connect(i * n + j, x * n + y);
                }
            }
        }
        int result = 0;
        for (const auto& [i, j] : landsNotOnBoudary) {
            if (!uf.isConnected(kVirtual, i * n + j)) {
                result++;
            }
        }
        return result;
    }
};