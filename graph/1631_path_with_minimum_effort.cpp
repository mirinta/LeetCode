#include <array>
#include <climits>
#include <cmath>
#include <tuple>
#include <queue>
#include <vector>

/**
 * Your are a hiker preparing for an upcoming hike. You are given "heights", a 2D array of size row
 * x columns, where hights[row][col] represents the height of cell (row, col). You are situated in
 * the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows - 1, columns -
 * 1). You can move up, down, left, or right, and you wish to find a route that requires the minimum
 * effort.
 *
 * A route's effort is the maximum absolute difference in heights between two consecutive cells of
 * the route.
 *
 * Return the minimum effort required to travel from the top-left cell to the bottom-right cell.
 *
 * ! rows == heights.length
 * ! columns == heights[i].length
 * ! 1 <= rows, columns <= 100
 * ! 1 <= heights[i][j] <= 10^6
 */

class UnionFind
{
public:
    explicit UnionFind(int n) : root(n), rank(n), count(n)
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

        if (rank[rootP] > root[rootQ]) {
            root[rootQ] = rootP;
        } else if (rank[rootP] < root[rootQ]) {
            root[rootP] = root[rootQ];
        } else {
            root[rootQ] = rootP;
            rank[rootP]++;
        }
        count--;
    }

private:
    std::vector<int> root;
    std::vector<int> rank;
    int count;
};

class Solution
{
public:
    int minimumEffortPath(std::vector<std::vector<int>>& heights) { return approach3(heights); }

private:
    const std::vector<std::pair<int, int>> kDirections{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Union-Find, time O(mn(log(mn)), space (mn)
    int approach3(std::vector<std::vector<int>>& heights)
    {
        std::vector<std::tuple<int, int, int>> edges;
        const int m = heights.size();
        const int n = heights[0].size();
        auto encode = [n](int i, int j) { return i * n + j; };
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i + 1 < m) { // go down, (i,j) to (i+1,j)
                    edges.push_back({std::abs(heights[i][j] - heights[i + 1][j]), encode(i, j),
                                     encode(i + 1, j)});
                }
                if (j + 1 < n) { // go right, (i,j) to (i,j+1)
                    edges.push_back({std::abs(heights[i][j] - heights[i][j + 1]), encode(i, j),
                                     encode(i, j + 1)});
                }
            }
        }
        if (edges.empty())
            return 0;

        std::sort(edges.begin(), edges.end(),
                  [](const auto& t1, const auto& t2) { return std::get<0>(t1) < std::get<0>(t2); });
        UnionFind uf(m * n);
        const int source = 0;
        const int destination = m * n - 1;
        for (const auto& [effort, p, q] : edges) {
            uf.connect(p, q);
            if (uf.isConnected(source, destination))
                return effort;
        }
        return -1;
    }

    // Dijkstra's algorithm, time O(mnlog(mn)), space O(mn)
    int approach2(std::vector<std::vector<int>>& heights)
    {
        const int m = heights.size();
        const int n = heights[0].size();
        std::vector<std::vector<int>> effortTo(m, std::vector<int>(n, INT_MAX));
        effortTo[0][0] = 0;
        using Tuple = std::tuple<int, int, int>; // <effort, x, y>
        auto comparator = [](const auto& t1, const auto& t2) -> bool {
            return std::get<0>(t1) > std::get<0>(t2);
        };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(comparator)> pq(comparator);
        pq.push({0, 0, 0});
        while (!pq.empty()) {
            const auto [effort, x, y] = pq.top();
            pq.pop();
            if (x == m - 1 && y == n - 1)
                return effort;

            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n)
                    continue;

                const int newEffort = std::max(effort, std::abs(heights[x][y] - heights[i][j]));
                if (effortTo[i][j] > newEffort) {
                    effortTo[i][j] = newEffort;
                    pq.push({effortTo[i][j], i, j});
                }
            }
        }
        return effortTo[m - 1][n - 1];
    }

    // binary search + BFS, time O(mnlog(10^6))=O(mn), space O(mn)
    int approach1(std::vector<std::vector<int>>& heights)
    {
        // search min effort
        int lo = 0;
        int hi = 1e6;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, heights)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

    bool isValid(int maxEffort, const std::vector<std::vector<int>>& heights)
    {
        // source: top-left
        // destination: bottom-right
        const int m = heights.size();
        const int n = heights[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        visited[0][0] = true;
        std::queue<std::pair<int, int>> queue;
        queue.push({0, 0});
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto [x, y] = queue.front();
                queue.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    if (visited[i][j] || std::abs(heights[i][j] - heights[x][y]) > maxEffort)
                        continue;

                    visited[i][j] = true;
                    queue.push({i, j});
                }
            }
        }
        return visited[m - 1][n - 1]; // check the destination is visited
    }
};