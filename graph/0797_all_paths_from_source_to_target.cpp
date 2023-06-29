#include <vector>

/**
 * Given a directed acyclic graph (DAG) of "n" nodes labeled from 0 to n - 1, find all possible
 * paths from node 0 to node n - 1 and return them in any order.
 *
 * The graph is given as follows: graph[i] is a list of all nodes you can visit from node i (i.e.,
 * there is a directed edge from node i to node graph[i][j]).
 *
 * ! n == graph.length
 *
 * ! 2 <= n <= 15
 *
 * ! 0 <= graph[i][j] < n
 *
 * ! graph[i][j] != i (i.e., there will be no self-loops)
 *
 * ! All the elements of graph[i] are unique.
 *
 * ! The input graph is guaranteed to be a DAG.
 */

class Solution
{
public:
    std::vector<std::vector<int>> allPathsSourceTarget(std::vector<std::vector<int>>& graph)
    {
        // since the graph is a DAG, we don't need a "visited" array
        result.clear();
        std::vector<int> path;
        backtrack(path, 0, graph.size() - 1, graph);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void backtrack(std::vector<int>& path, int source, int destination,
                   const std::vector<std::vector<int>>& graph)
    {
        if (source == destination) {
            result.push_back(path);
            result.back().push_back(destination);
            return;
        }
        path.push_back(source);
        for (const auto& adjacent : graph[source]) {
            backtrack(path, adjacent, destination, graph);
        }
        path.pop_back();
    }
};
