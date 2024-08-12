#include <vector>

/**
 * There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections
 * forming a network where connections[i] = [ai, bi] represents a connection between servers ai and
 * bi. Any server can reach other servers directly or indirectly through the network.
 *
 * A critical connection is a connection that, if removed, will make some servers unable to reach
 * some other server.
 *
 * Return all critical connections in the network in any order.
 *
 * ! 2 <= n <= 10^5
 * ! n - 1 <= connections.length <= 10^5
 * ! 0 <= ai, bi <= n - 1
 * ! ai != bi
 * ! There are no repeated connections.
 */

class Solution
{
public:
    std::vector<std::vector<int>> criticalConnections(int n,
                                                      std::vector<std::vector<int>>& connections)
    {
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : connections) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        visited.assign(n, false);
        dfn.assign(n, -1);
        low.assign(n, -1);
        std::vector<std::vector<int>> bridges;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(bridges, i, -1, graph);
            }
        }
        return bridges;
    }

private:
    int time;
    std::vector<bool> visited;
    std::vector<int> dfn;
    std::vector<int> low;

    void dfs(std::vector<std::vector<int>>& bridges, int current, int parent,
             const std::vector<std::vector<int>>& graph)
    {
        visited[current] = true;
        dfn[current] = time;
        low[current] = time;
        time++;
        for (const auto& child : graph[current]) {
            if (child == parent)
                continue;

            if (!visited[child]) {
                dfs(bridges, child, current, graph);
                low[current] = std::min(low[current], low[child]);
                if (low[child] > dfn[current]) {
                    bridges.push_back({current, child});
                }
            } else {
                low[current] = std::min(low[current], dfn[child]);
            }
        }
    }
};
