#include <cstddef>
#include <queue>
#include <vector>

/**
 * You are given an undirected weighted graph of "n" nodes (0-indexed), represented by an edge list
 * where edges[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability of
 * success of traversing that edge succProb[i].
 *
 * Given two nodes start and end, find the path with the maximum probability of success to go from
 * start to end and return its success probability.
 *
 * It there is no path from start to end, return 0. Your answer will be accepted if it differs from
 * the correct answer by at mode 1e-5.
 */

class Solution
{
public:
    double maxProbability(int n, std::vector<std::vector<int>>& edges,
                          std::vector<double>& succProb, int start, int end)
    {
        // build graph: graph[from] = [<prob, to>, ...]
        std::vector<std::vector<std::pair<double, int>>> graph(n);
        for (size_t i = 0; i < edges.size(); ++i) {
            const auto& from = edges[i][0];
            const auto& to = edges[i][1];
            const auto& prob = succProb[i];
            // bidirectional graph
            graph[from].push_back({prob, to});
            graph[to].push_back({prob, from});
        }
        // find the maximum path using Dijkstra's algorithm
        std::vector<double> probTo(n, -1);
        probTo[start] = 1;                                   // probability to itself is 1.0
        std::priority_queue<std::pair<double, int>> maxHeap; // <prob, id>
        maxHeap.push({1, start});
        while (!maxHeap.empty()) {
            const auto v = maxHeap.top().second;
            maxHeap.pop();
            if (v == end)
                return probTo[v];

            for (const auto& [prob, to] : graph[v]) {
                const auto newProb = probTo[v] * prob;
                if (newProb > probTo[to]) {
                    probTo[to] = newProb;
                    maxHeap.push({newProb, to});
                }
            }
        }
        return 0;
    }
};
