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
 *
 * ! 2 <= n <= 10^4
 * ! 0 <= start, end < n
 * ! start != end
 * ! 0 <= a, b < n
 * ! a != b
 * ! 0 <= succProb.length == edges.length <= 2*10^4
 * ! 0 <= succProb[i] <= 1
 * ! There is at most one edge between every two nodes.
 */

class Solution
{
public:
    double maxProbability(int n, std::vector<std::vector<int>>& edges,
                          std::vector<double>& succProb, int start_node, int end_node)
    {
        return approach3(n, edges, succProb, start_node, end_node);
    }

private:
    // Bellman-Ford (DP with space optimization), time O(EV), space O(V)
    double approach3(int n, const std::vector<std::vector<int>>& edges,
                     const std::vector<double>& succProb, int src, int dst)
    {
        std::vector<double> dp(n, 0);
        std::vector<double> iMinus1(n, 0);
        iMinus1[src] = 1.0;
        for (int i = 1; i < n; ++i) {
            bool update = false;
            for (int j = 0; j < edges.size(); ++j) {
                const auto& from = edges[j][0];
                const auto& to = edges[j][1];
                const auto& prob = succProb[j];
                if (iMinus1[from] * prob > dp[to]) {
                    dp[to] = iMinus1[from] * prob;
                    update = true;
                }
                if (iMinus1[to] * prob > dp[from]) {
                    dp[from] = iMinus1[to] * prob;
                    update = true;
                }
            }
            if (!update)
                break;

            iMinus1 = dp;
        }
        return dp[dst];
    }

    // DP, !!! Memory Limit Exceeded !!!, time O(EV), space O(V^2)
    double approach2(int n, const std::vector<std::vector<int>>& edges,
                     const std::vector<double>& succProb, int src, int dst)
    {
        // dp[i][j] = max prob from src to j with at most i edges
        // - the optimal path from src to dst contains at most n-1 edges
        std::vector<std::vector<double>> dp(n, std::vector<double>(n, 0));
        dp[0][src] = 1.0;
        double result = 0;
        for (int i = 1; i < n; ++i) {
            bool update = false;
            for (int j = 0; j < edges.size(); ++j) {
                const auto& from = edges[j][0];
                const auto& to = edges[j][1];
                const auto& prob = succProb[j];
                if (dp[i - 1][from] * prob > dp[i][to]) {
                    dp[i][to] = dp[i - 1][from] * prob;
                    update = true;
                }
                if (dp[i - 1][to] * prob > dp[i][from]) {
                    dp[i][from] = dp[i - 1][to] * prob;
                    update = true;
                }
            }
            if (!update)
                break;

            result = std::max(result, dp[i][dst]);
        }
        return result;
    }

    // Dijkstra's algorithm, time O(E+ElogV), space O(E+V)
    double approach1(int n, const std::vector<std::vector<int>>& edges,
                     const std::vector<double>& succProb, int src, int dst)
    {
        using Pair = std::pair<double, int>; // <prob, vertex>
        std::vector<std::vector<Pair>> graph(n);
        for (int i = 0; i < edges.size(); ++i) {
            const auto& from = edges[i][0];
            const auto& to = edges[i][1];
            const auto& prob = succProb[i];
            graph[from].push_back({prob, to});
            graph[to].push_back({prob, from});
        }
        auto comparator = [](const auto& p1, const auto& p2) { return p1.first < p2.first; };
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(
            comparator); // max heap
        pq.push({1.0, src});
        std::vector<double> probTo(n, -1);
        probTo[src] = 1.0;
        while (!pq.empty()) {
            const int v = pq.top().second;
            pq.pop();
            if (v == dst)
                return probTo[v];

            for (const auto& [prob, adj] : graph[v]) {
                if (probTo[adj] < probTo[v] * prob) {
                    probTo[adj] = probTo[v] * prob;
                    pq.push({probTo[adj], adj});
                }
            }
        }
        return 0;
    }
};
