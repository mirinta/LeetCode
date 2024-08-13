#include <functional>
#include <stack>
#include <vector>

using Graph = const std::vector<std::vector<int>>;

std::vector<int> findArticulationPoints(const Graph& graph)
{
    const int n = graph.size();
    int time = 0;
    std::vector<int> dfn(n, -1);
    std::vector<int> low(n, -1);
    std::vector<bool> isAP(n, false); // result[i] = whether vertex i is an articulation point
    // -----------------------------------------------------------------
    std::function<int(int, int)> dfs = [&](int current, int parent) {
        int unvisitedChildren = 0;
        dfn[current] = low[current] = ++time;
        for (const auto& next : graph[current]) {
            if (next == parent)
                continue;

            if (dfn[next] == -1) {
                unvisitedChildren++;
                dfs(next, current);
                if (low[next] >= dfn[current]) {
                    isAP[current] = true;
                }
                low[current] = std::min(low[current], low[next]);
            } else {
                low[current] = std::min(low[current], dfn[next]);
            }
        }
        return unvisitedChildren;
    };
    // -----------------------------------------------------------------
    std::vector<int> result;
    for (int i = 0; i < n; ++i) {
        if (dfn[i] == -1) {
            isAP[i] = dfs(i, -1) > 1;
        }
        if (isAP[i]) {
            result.push_back(i);
        }
    }
    return result;
}