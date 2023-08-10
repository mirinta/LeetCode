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
        clock = 0;
        visited = std::vector<bool>(n, false);
        disc = std::vector<int>(n, -1);
        low = std::vector<int>(n, -1);
        std::vector<std::vector<int>> bridges;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(bridges, i, -1, graph);
            }
        }
        return bridges;
    }

private:
    int clock;
    std::vector<bool> visited;
    std::vector<int> disc; // disc[i] is the earliest time of visiting vertex i
    std::vector<int> low;  // low[i] is the earliest time of visiting any vertex reachable from
                           // vertex i through i's DFS subtree, including i itself

    void dfs(std::vector<std::vector<int>>& bridges, int current, int parent,
             const std::vector<std::vector<int>>& graph)
    {
        visited[current] = true;
        disc[current] = clock;
        low[current] = clock;
        clock++;
        for (const auto& adj : graph[current]) {
            if (adj == parent)
                continue;

            if (!visited[adj]) {
                dfs(bridges, adj, current, graph);
                low[current] = std::min(low[current], low[adj]);
                if (low[adj] > disc[current]) {
                    bridges.push_back({current, adj}); // found a bridge
                }
            } else {
                low[current] = std::min(low[current], disc[adj]);
            }
        }
    }
};