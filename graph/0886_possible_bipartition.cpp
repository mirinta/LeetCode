#include <vector>

/**
 * We want to split a group of "n" people (labeled from 1 to n) into groups of any size. Each person
 * may dislike some other people, and they should not go into the same group.
 *
 * Given the integer "n" and the array "dislikes" where dislike[i] = [ai, bi] indicates that the
 * person labeled ai does not like the person labeled bi, return true if it is possible to split
 * everyone into two groups in this way.
 */

class Solution
{
public:
    bool possibleBipartition(int n, std::vector<std::vector<int>>& dislikes)
    {
        // build undirected graph
        std::vector<std::vector<int>> graph(n, std::vector<int>{});
        for (const auto& pair : dislikes) {
            // pi = [ai, bi], ai and bi are 1-indexed
            const auto from = pair[0] - 1;
            const auto to = pair[1] - 1;
            graph[from].push_back(to);
            graph[to].push_back(from);
        }
        // initialize
        result = true;
        visited = std::vector<bool>(n, false);
        color = std::vector<bool>(n, false);
        for (size_t s = 0; s < graph.size(); ++s) {
            if (!visited[s]) {
                dfs(graph, s);
            }
        }
        return result;
    }

private:
    bool result = true;
    std::vector<bool> visited;
    std::vector<bool> color;

    void dfs(const std::vector<std::vector<int>>& graph, int s)
    {
        if (!result)
            return;

        visited[s] = true;
        for (const auto& adj : graph[s]) {
            if (!visited[adj]) {
                color[adj] = !color[s];
                dfs(graph, adj);
            } else {
                if (color[adj] == color[s]) {
                    result = false;
                    return;
                }
            }
        }
    }
};