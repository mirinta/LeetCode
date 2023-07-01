#include <queue>
#include <vector>

/**
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return
 * the number of islands.
 *
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or
 * vertically. You may assume all four edges of the grid are all surrounded by water.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 300
 * ! grid[i][j] is '0' or '1'.
 */

class Solution
{
public:
    int numIslands(std::vector<std::vector<char>>& grid) { return approach3(grid); }

private:
    static constexpr char kLand = '1';
    static constexpr char kWater = '0';
    const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // approach3: BFS
    int approach3(std::vector<std::vector<char>>& grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;

        const int m = grid.size();
        const int n = grid[0].size();
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != kLand)
                    continue;

                result++;
                std::queue<std::pair<int, int>> queue;
                queue.push({i, j});
                grid[i][j] = kWater;
                while (!queue.empty()) {
                    const auto [x, y] = queue.front();
                    queue.pop();
                    for (const auto& [dx, dy] : kDirections) {
                        const int newX = x + dx;
                        const int newY = y + dy;
                        if (newX < 0 || newX >= m || newY < 0 || newY >= n ||
                            grid[newX][newY] != kLand)
                            continue;

                        queue.push({newX, newY});
                        grid[newX][newY] = kWater;
                    }
                }
            }
        }
        return result;
    }

    // approach2: DFS
    int approach2(std::vector<std::vector<char>>& grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;

        const int m = grid.size();
        const int n = grid[0].size();
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == kLand) {
                    dfs(i, j, grid);
                    result++;
                }
            }
        }
        return result;
    }

    void dfs(int x, int y, std::vector<std::vector<char>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != kLand)
            return;

        grid[x][y] = kWater;
        for (const auto& [dx, dy] : kDirections) {
            dfs(x + dx, y + dy, grid);
        }
    }

    // approach1 : UnionFind
    class UnionFind
    {
    public:
        explicit UnionFind(int n1, int n2) : _root(n1), _rank(n1), _count(n2)
        {
            for (int i = 0; i < n1; ++i) {
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

    private:
        std::vector<int> _root;
        std::vector<int> _rank;
        int _count;
    };

    int approach1(std::vector<std::vector<char>>& grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;

        const int m = grid.size();
        const int n = grid[0].size();
        int numOfLands = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == kLand) {
                    numOfLands++;
                }
            }
        }
        UnionFind uf(m * n, numOfLands);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == kLand) {
                    for (const auto& [dx, dy] : kDirections) {
                        const int x = i + dx;
                        const int y = j + dy;
                        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != kLand)
                            continue;

                        uf.connect(i * n + j, x * n + y);
                    }
                }
            }
        }
        return uf.count();
    }
};