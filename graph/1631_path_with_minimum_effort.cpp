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

    bool isConnected(int p, int q) { return find(p) == find(q); }

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
            root[rootP] = rootQ;
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
    int minimumEffortPath(std::vector<std::vector<int>>& heights) { return approach1(heights); }

private:
    static const std::vector<std::pair<int, int>> kDirections;

    // UnionFind, time O(MNlogMN), space O(MN)
    int approach3(const std::vector<std::vector<int>>& heights)
    {
        const int m = heights.size();
        const int n = heights[0].size();
        using Edge = std::tuple<int, int, int>; // <from, to, effort>
        std::vector<Edge> edges;
        auto encode = [&n](int x, int y) { return x * n + y; };
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i + 1 < m) { // go right
                    edges.emplace_back(encode(i, j), encode(i + 1, j),
                                       std::abs(heights[i][j] - heights[i + 1][j]));
                }
                if (j + 1 < n) { // go left
                    edges.emplace_back(encode(i, j), encode(i, j + 1),
                                       std::abs(heights[i][j] - heights[i][j + 1]));
                }
            }
        }
        if (edges.empty())
            return 0;

        std::sort(edges.begin(), edges.end(),
                  [](const auto& e1, const auto& e2) { return std::get<2>(e1) < std::get<2>(e2); });
        UnionFind uf(m * n);
        const int src = 0;
        const int dest = m * n - 1;
        for (const auto& [x, y, effort] : edges) {
            uf.connect(x, y);
            if (uf.isConnected(src, dest))
                return effort;
        }
        return -1;
    }

    // Binary search + BFS, time O(MNlog(10^6))=O(MN), space O(MN)
    int approach2(const std::vector<std::vector<int>>& heights)
    {
        // search the min effort
        int lo = 0;
        int hi = 1e6; // one of the problem's constraints
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
        // source (0,0), destination (m-1,n-1)
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
                if (x == m - 1 && y == n - 1)
                    return true;

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
        return false;
    }

    // Dijkstra's algorithm, time O(MNlogMN), space O(MN)
    int approach1(const std::vector<std::vector<int>>& heights)
    {
        const int m = heights.size();
        const int n = heights[0].size();
        std::vector<std::vector<int>> effortTo(m, std::vector<int>(n, INT_MAX));
        effortTo[0][0] = 0;
        using Tuple = std::tuple<int, int, int>; // <x, y, effort to this point>
        auto comparator = [](const auto& t1, const auto& t2) {
            return std::get<2>(t1) > std::get<2>(t2);
        };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(comparator)> pq(
            comparator); // min heap
        pq.push({0, 0, 0});
        while (!pq.empty()) {
            const auto [x, y, effort] = pq.top();
            pq.pop();
            if (x == m - 1 && y == n - 1)
                return effort;

            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n)
                    continue;

                const int newEffort = std::max(effort, std::abs(heights[i][j] - heights[x][y]));
                if (effortTo[i][j] > newEffort) {
                    effortTo[i][j] = newEffort;
                    pq.push({i, j, newEffort});
                }
            }
        }
        return -1;
    }
};

const std::vector<std::pair<int, int>> Solution::kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};