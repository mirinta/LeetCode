#include <queue>
#include <vector>

/**
 * This is an undirected graph with "n" nodes, where each node is numbered between 0 and n - 1. You
 * are given a 2D array "graph", where graph[u] is an array of nodes that node "u" is adjacent to.
 * More formally, for each "v" in graph[u], there is an undirected edge between node "u" and node
 * "v". The graph has the following properties:
 *
 * - Thee are no self-edges (graph[u] does not contain u).
 *
 * - There are no parallel edges (graph[u] does not contain duplicate values).
 *
 * - If v is in graph[u], then u is in graph[v] (the graph is undirected).
 *
 * - The graph may not be connected, meaning there may be two nodes u and v such that there is no
 * path between them.
 *
 * A graph is bipartite if the nodes can be partitioned into two independent sets "A" and "B" such
 * that every edge in the graph connects a node in set "A" and a node in set "B".
 *
 * Return true if and only if it is bipartite.
 */

class Solution
{
public:
    bool isBipartite(std::vector<std::vector<int>>& graph)
    {
        result = true;
        visited = std::vector<int>(graph.size(), false);
        color = std::vector<bool>(graph.size(), false);
        for (size_t v = 0; v < graph.size(); ++v) {
            // approach 1: dfs
            dfs(graph, v);
            // approach 2: bfs
            // bfs(graph, v);
        }
        return result;
    }

private:
    bool result = true;
    std::vector<int> visited;
    std::vector<bool> color; // true and false represent different colors

    void bfs(const std::vector<std::vector<int>>& graph, int v)
    {
        if (!result || visited[v])
            return;

        visited[v] = true;
        std::queue<int> queue;
        queue.push(v);
        while (!queue.empty() && result) {
            const auto top = queue.front();
            queue.pop();
            for (const auto& w : graph[top]) {
                if (!visited[w]) {
                    color[w] = !color[top];
                    visited[w] = true;
                    queue.push(w);
                } else {
                    if (color[w] == color[top]) {
                        result = false;
                        return;
                    }
                }
            }
        }
    }

    void dfs(const std::vector<std::vector<int>>& graph, int v)
    {
        if (!result || visited[v])
            return;

        visited[v] = true;
        for (const auto& adj : graph[v]) {
            if (!visited[adj]) {
                color[adj] = !color[v]; // paint the adjacent node with a different color
                dfs(graph, adj);
            } else {
                if (color[adj] == color[v]) {
                    result = false;
                    return;
                }
            }
        }
    }
};