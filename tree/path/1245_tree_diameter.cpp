#include <vector>

/**
 * The diameter of a tree is the number of edges in the longest path in that tree.
 *
 * There is an undirected tree of n nodes labeled from 0 to n - 1. You are given a 2D array edges
 * where edges.length == n - 1 and edges[i] = [ai, bi] indicates that there is an undirected edge
 * between nodes ai and bi in the tree.
 *
 * Return the diameter of the tree.
 *
 * ! n == edges.length + 1
 * ! 1 <= n <= 10^4
 * ! 0 <= ai, bi < n
 * ! ai != bi
 */

class Solution
{
public:
    int treeDiameter(std::vector<std::vector<int>>& edges)
    {
        if (edges.empty())
            return 0;

        // #NOTE# length of a path = number of edges = number of nodes - 1
        // Here, we define the length of a path = the number of nodes along the path.
        const int n = edges.size() + 1;
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        std::vector<bool> visited(n, false);
        visited[0] = true; // we can start with any node
        int result = 0;
        dfs(result, visited, 0, graph);
        return result == 0 ? 0 : result - 1;
    }

private:
    int dfs(int& result, std::vector<bool>& visited, int root,
            const std::vector<std::vector<int>>& graph)
    {
        int longest = 0;
        int secondLongest = 0;
        for (const auto& child : graph[root]) {
            if (visited[child])
                continue;

            visited[child] = true;
            const int subreeLongest = dfs(result, visited, child, graph);
            if (subreeLongest > longest) {
                secondLongest = longest;
                longest = subreeLongest;
            } else if (subreeLongest > secondLongest) {
                secondLongest = subreeLongest;
            }
            result = std::max(result, 1 + longest + secondLongest); // +1 to include the root node
        }
        return 1 + longest; // +1 to include the root node
    }
};