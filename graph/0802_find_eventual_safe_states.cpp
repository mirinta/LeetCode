#include <queue>
#include <vector>

/**
 * There is a directed graph of n nodes with each node labeled from 0 to n - 1. The graph is
 * represented by a 0-indexed 2D integer array graph where graph[i] is an integer array of nodes
 * adjacent to node i, meaning there is an edge from node i to each node in graph[i].
 *
 * A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible
 * path starting from that node leads to a terminal node (or another safe node).
 *
 * Return an array containing all the safe nodes of the graph. The answer should be sorted in
 * ascending order.
 *
 * ! n == graph.length
 * ! 1 <= n <= 10^4
 * ! 0 <= graph[i].length <= n
 * ! 0 <= graph[i][j] <= n - 1
 * ! graph[i] is sorted in a strictly increasing order.
 * ! The graph may contain self-loops.
 * ! The number of edges in the graph will be in the range [1, 4 * 10^4].
 */

class Solution
{
public:
    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>>& graph)
    {
        // a node is safe = start from this code, there's no cycle
        return approach1(graph);
    }

private:
    enum Color { White, Gray, Black };
    // DFS, detect cycles with colors
    std::vector<int> approach1(std::vector<std::vector<int>>& graph)
    {
        const int n = graph.size();
        std::vector<Color> colors(n, White);
        std::vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (!hasCycle(colors, i, graph)) {
                result.push_back(i);
            }
        }
        return result;
    }

    bool hasCycle(std::vector<Color>& colors, int v, const std::vector<std::vector<int>>& graph)
    {
        colors[v] = Gray;
        for (const auto& adj : graph[v]) {
            if (colors[adj] == Gray)
                return true;

            if (colors[adj] == White && hasCycle(colors, adj, graph))
                return true;
        }
        colors[v] = Black;
        return false;
    }

    // Kahn's algorithm (the original graph needs to be reversed)
    std::vector<int> approach2(std::vector<std::vector<int>>& graph)
    {
        const int n = graph.size();
        std::vector<std::vector<int>> reversedGraph(n, std::vector<int>());
        std::vector<int> indegrees(n, 0);
        for (int i = 0; i < n; ++i) {
            for (const auto& adj : graph[i]) {
                reversedGraph[adj].push_back(i);
                indegrees[i]++;
            }
        }
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (indegrees[i] == 0) {
                queue.push(i);
            }
        }
        std::vector<bool> isSafe(n, false); // The answer should be sorted in ascending order.
        while (!queue.empty()) {
            const int v = queue.front();
            queue.pop();
            isSafe[v] = true;
            for (const auto& adj : reversedGraph[v]) {
                if (--indegrees[adj] == 0) {
                    queue.push(adj);
                }
            }
        }
        std::vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (isSafe[i]) {
                result.push_back(i);
            }
        }
        return result;
    }
};
