#include <queue>
#include <vector>

/**
 * @brief Adjacency matrix (0-indexed square matrix).
 *
 * @note graph[i][x] = {j, w} indicates that there is an directed edge from vertex i to vertex j
 * with weight w.
 */
using Graph = std::vector<std::vector<std::pair<int, long long>>>;

using Edges = std::vector<std::tuple<int, int, long long>>; // <from, to, weight>

/**
 * @brief Calculate the weights of shortest paths for all pairs of vertices using the Floyd-Warshall
 * algorithm.
 *
 * @note Negative edge weights are allowed, but the given graph must not have negative cycles.
 *
 * @note The returned matrix is 0-indexed.
 *
 * @note matrix[i][j] = LLONG_MAX indicates that it is not reachable from i to j.
 *
 * @note Time Complexity = O(V^3), Space Complexity = O(V^2), where V is the number of vertices.
 */
std::vector<std::vector<long long>> floydWarshall(const Graph& graph)
{
    const int n = graph.size();
    std::vector<std::vector<long long>> dist(n, std::vector<long long>(n, LLONG_MAX));
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        for (const auto& [j, weight] : graph[i]) {
            dist[i][j] = std::min(dist[i][j], weight);
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (dist[i][k] == LLONG_MAX)
                continue;

            for (int j = 0; j < n; ++j) {
                if (dist[k][j] == LLONG_MAX)
                    continue;

                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
}

/**
 * @brief Calculate the weight of the shortest path from src to dst using the Dijkstra's algorithm.
 *
 * @note The given graph must not have negative edge weights.
 *
 * @note Return LLONG_MAX if it is not reachable from src to dst.
 *
 * @note Time Complexity = O(V + ElogV), Space Complexity = O(V), where E and V are the number of
 * vertices and edges, respectively.
 */
long long dijkstra(int src, int dst, const Graph& graph)
{
    const int n = graph.size();
    std::vector<long long> distTo(n, LLONG_MAX);
    distTo[src] = 0;
    using Pair = std::pair<int, long long>; // <vertex v, weights from src to v>
    auto comparator = [](const Pair& p1, const Pair& p2) { return p1.second > p2.second; };
    std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator); // min heap;
    pq.emplace(0, src);
    while (!pq.empty()) {
        const auto [v, weights] = pq.top();
        pq.pop();
        if (v == dst)
            return weights;

        if (weights > distTo[v])
            continue;

        for (const auto& [adj, weight] : graph[v]) {
            if (distTo[v] + weight < distTo[adj]) {
                distTo[adj] = distTo[v] + weight;
                pq.emplace(adj, distTo[adj]);
            }
        }
    }
    return LLONG_MAX;
}

/**
 * @brief Calculate the weight of the shortest path from src to dst using the Bellman-Ford
 * algorithm.
 *
 * @note Negative edge weights are allowed, but the given graph must not have negative cycles.
 *
 * @note Return LLONG_MAX if it is not reachable from src to dst.
 *
 * @note Time Complexity = O(EV), Space Complexity = O(V), where E and V are the number of vertices
 * and edges, respectively.
 */
long long bellmanFord(int src, int dst, int V, const Edges& edges)
{
    std::vector<long long> dp(V, LLONG_MAX);
    dp[src] = 0;
    std::vector<long long> prev(V);
    for (int i = 1; i <= V - 1; ++i) {
        prev.assign(dp.begin(), dp.end());
        std::fill(dp.begin(), dp.end(), LLONG_MAX);
        bool updated = false;
        for (const auto& [from, to, weight] : edges) {
            if (prev[from] != LLONG_MAX && prev[from] + weight < dp[to]) {
                updated = true;
                dp[to] = prev[from] + weight;
            }
        }
        if (!updated)
            break;
    }
    long long result = LLONG_MAX;
    for (int i = 1; i <= V - 1; ++i) {
        result = std::min(result, dp[dst]);
    }
    return result;
}
