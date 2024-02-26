#include <algorithm>
#include <queue>
#include <vector>

#include "UnionFind.cpp"

/**
 * @brief Adjacency matrix (0-indexed square matrix).
 *
 * @note graph[i][x] = {j, w} indicates that there is an undirected edge between vertex i and vertex
 * j with weight w.
 */
using Graph = std::vector<std::vector<std::pair<int, long long>>>;

using Edges = std::vector<std::tuple<int, int, long long>>; // <from, to, weight>

/**
 * @brief Return the total weight of the minimum spanning tree (MST) using the Kruskal's algorithm.
 *
 * @note Return LLONG_MAX if the given graph is not connected.
 *
 * @note Time Complexity = O(ElogE + Eα(V)), Space Complexity = O(std::sort + V), where α refers to
 * the Inverse Ackermann function. E and V are the number of edges and vertices, respectively.
 */
long long kruskal(Edges& edges, int V)
{
    UnionFind uf(V);
    std::sort(edges.begin(), edges.end(),
              [](const auto& t1, const auto& t2) { return std::get<2>(t1) < std::get<2>(t2); });
    long long result = 0;
    for (const auto& [i, j, weight] : edges) {
        if (!uf.isConnected(i, j)) {
            uf.connect(i, j);
            result += weight;
        }
    }
    return uf.numOfConnectedComponents() == 1 ? LLONG_MAX : result;
}

/**
 * @brief Return the total weight of the minimum spanning tree (MST) using the Prim's algorithm.
 *
 * @note Return LLONG_MAX if the given graph is not connected.
 *
 * @note Time Complexity = O(VlogV + ElogV), Space Complexity = O(V), where E and V are the number
 * of edges and vertices, respectively.
 */
long long prim(const Graph& graph)
{
    const int V = graph.size();
    using Pair = std::pair<int, long long>; // <v, weight>
    auto comparator = [](const Pair& p1, const Pair& p2) { return p1.second > p2.second; };
    std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator);
    // start from vertex 0
    for (const auto& [adj, weight] : graph[0]) {
        pq.emplace(adj, weight);
    }
    std::vector<bool> visited(V, false); // an edge(i,j) is visited iff both i and j are visited
    visited[0] = true;
    int edges = 0;
    long long result = 0;
    while (!pq.empty()) {
        const auto [v, weights] = pq.top();
        pq.pop();
        if (visited[v])
            continue;

        visited[v] = true;
        result += weights;
        edges++;
        for (const auto& [adj, weight] : graph[v]) {
            if (!visited[adj]) {
                pq.emplace(adj, weight);
            }
        }
    }
    return edges == V - 1 ? LLONG_MAX : result;
}
