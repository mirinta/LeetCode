#include <queue>
#include <unordered_set>
#include <vector>

/**
 * There are n cities numbered from 0 to n - 1 and n - 1 roads such that there is only one way to
 * travel between two different cities (this network form a tree). Last year, The ministry of
 * transport decided to orient the roads in one direction because they are too narrow.
 *
 * Roads are represented by connections where connections[i] = [ai, bi] represents a road from city
 * ai to city bi.
 *
 * This year, there will be a big event in the capital (city 0), and many people want to travel to
 * this city.
 *
 * Your task consists of reorienting some roads such that each city can visit the city 0. Return the
 * minimum number of edges changed.
 *
 * It's guaranteed that each city can reach city 0 after reorder.
 *
 * ! 2 <= n <= 5 * 10^4
 * ! connections.length == n - 1
 * ! connections[i].length == 2
 * ! 0 <= ai, bi <= n - 1
 * ! ai != bi
 */

class Solution
{
public:
    int minReorder(int n, std::vector<std::vector<int>>& connections)
    {
        // graph[from] = {<to,flag>...}
        // flag = 1 means it is an original path
        // flag = 0 means it is not an original path
        // we apply BFS starting from node 0, all the original paths should be reordered
        std::vector<std::vector<std::pair<int, int>>> graph(n, std::vector<std::pair<int, int>>());
        for (const auto& connection : connections) {
            const auto& from = connection[0];
            const auto& to = connection[1];
            graph[from].push_back({to, 1});
            graph[to].push_back({from, 0});
        }
        std::unordered_set<int> visited;
        visited.insert(0);
        std::queue<int> queue;
        queue.push(0);
        int result = 0;
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            for (const auto& [adj, flag] : graph[v]) {
                if (visited.count(adj))
                    continue;

                result += flag;
                visited.insert(adj);
                queue.push(adj);
            }
        }
        return result;
    }
};