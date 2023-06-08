#include <queue>
#include <tuple>
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
    int findCheapestPrice(int n, const std::vector<std::vector<int>>& flights, int src, int dst,
                          int k)
    {
        std::vector<std::vector<std::pair<int, int>>> graph(n, std::vector<std::pair<int, int>>{});
        for (const auto& flight : flights) {
            const auto& from = flight[0];
            const auto& to = flight[1];
            const auto& price = flight[2];
            graph[from].push_back({to, price});
        }
        // tuple<int, int, int>,
        // - tuple<2> = index of target vertex
        // - tuple<0> = total price from src to this target
        // - tuple<1> = edges from src to this target
        using Tuple = std::tuple<int, int, int>;
        std::priority_queue<Tuple, std::vector<Tuple>, std::greater<Tuple>> queue;
        queue.push({0, 0, src});
        std::vector<int> edgesTo(n, INT_MAX);
        while (!queue.empty()) {
            const auto [totalPrice, edges, v] = queue.top();
            queue.pop();
            if (edges >= edgesTo[v] || edges > k + 1)
                continue;

            if (v == dst)
                return totalPrice;

            edgesTo[v] = edges;
            for (const auto& [adj, price] : graph[v]) {
                queue.push({totalPrice + price, edges + 1, adj});
            }
        }
        return -1;
    }
};