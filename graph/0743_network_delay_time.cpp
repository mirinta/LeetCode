#include <climits>
#include <queue>
#include <vector>

/**
 * You are given a network of "n" nodes, labeled from 1 to n. You are also given "times", a list of
 * travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the
 * target node, and wi is the time it takes for a signal to travel from source to target.
 *
 * We will send a signal from a given node "k". Return the minimum time it takes for all the "n"
 * nodes to receive the signal. If it is impossible for all the "n" nodes to receive the signal,
 * return -1.
 *
 * ! 1 <= k <= n
 * ! 1 <= ui, vi <= n
 * ! ui != vi
 * ! 0 <= wi
 * ! All the paris (ui, vi) are unique. (i.e., no multiple edges)
 */

class Solution
{
private:
    struct DirectedEdge
    {
        int from;
        int to;
        int weight; // non-negative
        explicit DirectedEdge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
    };

    using Graph = std::vector<std::vector<DirectedEdge>>;
    std::vector<int> dijkstra(Graph& graph, int source)
    {
        if (graph.empty() || source < 0 || source >= graph.size())
            return {};

        std::vector<int> distTo(graph.size(), INT_MAX);
        distTo[source] = 0;
        auto comp = [&distTo](int v1, int v2) { return distTo[v1] > distTo[v2]; };
        std::priority_queue<int, std::vector<int>, decltype(comp)> minHeap(comp);
        minHeap.push(source);
        while (!minHeap.empty()) {
            const auto v = minHeap.top();
            minHeap.pop();
            for (const auto& edge : graph[v]) {
                // p = edge.from, q = edge.to, w = edge.weight
                // if distTo[q] > distTo[p] + w,
                // it means source->...->p->q is shorter than source->...->q
                const auto dist = distTo[edge.from] + edge.weight;
                if (distTo[edge.to] > dist) {
                    distTo[edge.to] = dist;
                    minHeap.push(edge.to);
                }
            }
        }
        return distTo;
    }

public:
    int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k)
    {
        // build digraph
        Graph graph(n, std::vector<DirectedEdge>{});
        for (const auto& t : times) {
            // t = [from, to, weight], from and to are 1-indexed
            graph[t[0] - 1].push_back(DirectedEdge{t[0] - 1, t[1] - 1, t[2]});
        }
        // find shortest path using Dijkstra's algorithm
        const auto distTo = dijkstra(graph, k - 1); // k is 1-indexed
        int result = INT_MIN;
        for (const auto& d : distTo) {
            if (d == INT_MAX) // node is unreachable
                return -1;

            result = std::max(result, d);
        }
        return result;
    }
};