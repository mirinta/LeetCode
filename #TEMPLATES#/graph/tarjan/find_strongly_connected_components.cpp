#include <functional>
#include <stack>
#include <vector>

using Graph = const std::vector<std::vector<int>>;

std::vector<std::vector<int>> findStronglyConnectedComponents(const Graph& graph)
{
    const int n = graph.size();
    int time = 0;
    std::vector<int> dfn(n, -1);
    std::vector<int> low(n, -1);
    std::stack<int> stack;
    std::vector<bool> inStack(n, false);
    std::vector<std::vector<int>> result;
    // -----------------------------------------------------------------
    std::function<void(int, int)> dfs = [&](int current, int parent) {
        dfn[current] = low[current] = ++time;
        stack.push(current);
        inStack[current] = true;
        for (const auto& next : graph[current]) {
            if (next == parent)
                continue;

            if (dfn[next] == -1) {
                dfs(next, current);
                low[current] = std::min(low[current], low[next]);
            } else if (inStack[next]) {
                low[current] = std::min(low[current], dfn[next]);
            }
        }
        if (low[current] == dfn[current]) {
            std::vector<int> scc;
            while (stack.top() != current) {
                scc.push_back(stack.top());
                inStack[stack.top()] = false;
                stack.pop();
            }
            scc.push_back(stack.top());
            inStack[stack.top()] = false;
            stack.pop();
            result.push_back(std::move(scc));
        }
    };
    // -----------------------------------------------------------------
    for (int i = 0; i < n; ++i) {
        if (dfn[i] == -1) {
            dfs(i, -1);
        }
    }
    return result;
}
