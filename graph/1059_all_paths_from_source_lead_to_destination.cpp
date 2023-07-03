#include <unordered_set>
#include <vector>

/**
 * Given the edges of a directed graph where edges[i] = [ai, bi] indicates there is an edge between
 * nodes ai and bi, and two nodes source and destination of this graph, determine whether or not all
 * paths starting from source eventually, end at destination, that is:
 *
 * - At least one path exists from the source node to the destination node
 *
 * - If a path exists from the source node to a node with no outgoing edges, then that node is equal
 * to destination.
 *
 * - The number of possible paths from source to destination is a finite number. Return true
 * if and only if all roads from source lead to destination.
 *
 * ! 1 <= n <= 10^4
 * ! 0 <= edges.length <= 10^4
 * ! edges.length == 2
 * ! 0 <= ai, bi <= n - 1
 * ! 0 <= source <= n - 1
 * ! 0 <= destination <= n - 1
 * ! The given graph may have self-loops and parallel edges.
 */

class Solution
{
public:
    bool leadsToDestination(int n, std::vector<std::vector<int>>& edges, int source,
                            int destination)
    {
        std::vector<std::vector<int>> graph(n, std::vector<int>());
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
        }
        std::vector<Color> colors(
            n, White); // -1 for not processed, 0 for being processed, 1 for process finished
        return dfs2(colors, source, destination, graph);
    }

private:
    enum Color { White, Gray, Black };
    bool dfs2(std::vector<Color>& colors, int source, int destination,
              const std::vector<std::vector<int>>& graph)
    {
        if (colors[source] != White)
            return colors[source] == Black;

        if (graph[source].empty())
            return source == destination;

        colors[source] = Gray;
        for (const auto& adj : graph[source]) {
            if (!dfs2(colors, adj, destination, graph))
                return false;
        }
        colors[source] = Black;
        return true;
    }

    bool approach1(int n, std::vector<std::vector<int>>& edges, int source, int destination)
    {
        std::vector<std::vector<int>> graph(n, std::vector<int>());
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
        }
        std::unordered_set<int> visited;
        visited.insert(source);
        std::unordered_set<int> path;
        return dfs1(visited, path, source, destination, graph);
    }

    bool dfs1(std::unordered_set<int>& visited, std::unordered_set<int>& path, int source,
              int destination, const std::vector<std::vector<int>>& graph)
    {
        if (source == destination)
            return graph[destination].empty();

        if (graph[source].empty())
            return source == destination;

        path.insert(source);
        for (const auto& adj : graph[source]) {
            if (path.count(adj))
                return false;

            if (visited.count(adj))
                continue;

            visited.insert(adj);
            if (!dfs1(visited, path, adj, destination, graph))
                return false;
        }
        path.erase(source);
        return true;
    }
};