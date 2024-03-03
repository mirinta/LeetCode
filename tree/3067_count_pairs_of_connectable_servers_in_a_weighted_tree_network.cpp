#include <vector>

/**
 * You are given an unrooted weighted tree with n vertices representing servers numbered from 0 to n
 * - 1, an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional edge between
 * vertices ai and bi of weight weighti. You are also given an integer signalSpeed.
 *
 * Two servers a and b are connectable through a server c if:
 *
 * - a < b, a != c and b != c.
 *
 * - The distance from c to a is divisible by signalSpeed.
 *
 * - The distance from c to b is divisible by signalSpeed.
 *
 * - The path from c to b and the path from c to a do not share any edges.
 *
 * Return an integer array count of length n where count[i] is the number of server pairs that are
 * connectable through the server i.
 *
 * ! 2 <= n <= 1000
 * ! edges.length == n - 1
 * ! edges[i].length == 3
 * ! 0 <= ai, bi < n
 * ! edges[i] = [ai, bi, weighti]
 * ! 1 <= weighti <= 10^6
 * ! 1 <= signalSpeed <= 10^6
 * ! The input is generated such that edges represents a valid tree.
 */

class Solution
{
public:
    std::vector<int> countPairsOfConnectableServers(std::vector<std::vector<int>>& edges,
                                                    int signalSpeed)
    {
        const int n = edges.size() + 1;
        Graph graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
            graph[edge[1]].emplace_back(edge[0], edge[2]);
        }
        std::vector<int> result(n, 0);
        for (int i = 0; i < n; ++i) {
            result[i] = solve(i, signalSpeed, graph);
        }
        return result;
    }

private:
    using Graph = std::vector<std::vector<std::pair<int, long long>>>;

    int solve(int root, int signalSpeed, const Graph& graph)
    {
        int sum = 0;
        int result = 0;
        for (const auto& [child, weight] : graph[root]) {
            int count = 0;
            dfs(count, child, root, weight, signalSpeed, graph);
            result += sum * count;
            sum += count;
        }
        return result;
    }

    void dfs(int& count, int root, int parent, long long sum, int signalSpeed, const Graph& graph)
    {
        if (sum % signalSpeed == 0) {
            count++;
        }
        for (const auto& [child, weight] : graph[root]) {
            if (child == parent)
                continue;

            dfs(count, child, root, weight + sum, signalSpeed, graph);
        }
    }
};