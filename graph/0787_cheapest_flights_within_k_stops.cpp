#include <array>
#include <queue>
#include <unordered_map>
#include <vector>

/**
 * There are n cities connected by some number of flights. You are given an array flights where
 * flights[i] = [from_i, to_i, price_i] indicates that there is a flight from city from_i to city
 * to_i with cost price_i.
 *
 * You are also given three integers src, dst, and k, return the cheapest price from src to dst with
 * at most k stops. If there is no such route, return -1.
 *
 * ! 1 <= n <= 100
 * ! 0 <= flights.length <= (n * (n - 1) / 2)
 * ! flights[i].length == 3
 * ! 0 <= from_i, to_i < n
 * ! from_i != to_i
 * ! 1 <= price_i <= 104
 * ! There will not be any multiple flights between two cities.
 * ! 0 <= src, dst, k < n
 * ! src != dst
 */

class Solution
{
public:
    int findCheapestPrice(int n, std::vector<std::vector<int>>& flights, int src, int dst, int k)
    {
        return approach1(n, flights, src, dst, k);
    }

private:
    int approach3(int n, std::vector<std::vector<int>>& flights, int src, int dst, int k)
    {
        // Bellman-Ford (DP with space optimization)
        std::vector<int> dp(n, INT_MAX);
        dp[src] = 0;
        for (int i = 1; i <= k + 1; ++i) {
            auto update = dp;
            for (const auto& flight : flights) {
                const auto& from = flight[0];
                const auto& to = flight[1];
                const auto& weight = flight[2];
                if (dp[from] == INT_MAX)
                    continue;

                update[to] = std::min(update[to], dp[from] + weight);
            }
            dp = update;
        }
        return dp[dst] == INT_MAX ? -1 : dp[dst];
    }

    int approach2(int n, std::vector<std::vector<int>>& flights, int src, int dst, int k)
    {
        // DP
        // - all edges have positive weights, no need to check negative cycle
        // - at most k stops means at most k+1 edges
        // dp[i][j] = min distance from src to j using at most i edges
        std::vector<std::vector<int>> dp(k + 2, std::vector<int>(n, INT_MAX));
        dp[0][src] = 0;
        int result = INT_MAX;
        for (int i = 1; i <= k + 1; ++i) {
            for (const auto& flight : flights) {
                const auto& from = flight[0];
                const auto& to = flight[1];
                const auto& weight = flight[2];
                if (dp[i - 1][from] == INT_MAX)
                    continue;

                dp[i][to] = std::min(dp[i][to], dp[i - 1][from] + weight);
            }
            result = std::min(result, dp[i][dst]);
        }
        return result == INT_MAX ? -1 : result;
    }

    int approach1(int n, std::vector<std::vector<int>>& flights, int src, int dst, int k)
    {
        // Dijkstra
        std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
        for (const auto& flight : flights) {
            graph[flight[0]].push_back({flight[1], flight[2]}); // from:[<to,price>,...]
        }
        using Triple = std::array<int, 3>; // <cost, steps, vertex>
        auto comp = [](const auto& t1, const auto& t2) -> bool { return t1[0] > t2[0]; };
        std::priority_queue<Triple, std::vector<Triple>, decltype(comp)> pq(comp);
        pq.push({0, 0, src});
        std::vector<int> stepsTo(n, INT_MAX);
        stepsTo[src] = 0;
        while (!pq.empty()) {
            const auto [cost, steps, v] = pq.top();
            pq.pop();
            if (steps > k + 1 || steps > stepsTo[v])
                continue;

            if (v == dst)
                return cost;

            stepsTo[v] = steps;
            for (const auto& [w, price] : graph[v]) {
                pq.push({cost + price, steps + 1, w});
            }
        }
        return -1;
    }
};
