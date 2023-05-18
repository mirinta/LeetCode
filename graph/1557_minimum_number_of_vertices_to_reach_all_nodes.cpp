#include <vector>

/**
 * Given a directed acyclic graph, with "n" vertices numbered from 0 to n - 1, and an array "edges"
 * where "edges[i] = [from_i, to_i]" represents a directed edge from node "from_i" to node "to_i".
 *
 * Find the smallest set of vertices from which all nodes in the graph are reachable. It's
 * guaranteed that a unique solution exists.
 *
 * Notice that you can return the vertices in any order.
 *
 * ! n >= 2
 * ! edges.length >= 1
 * ! edges[i].length == 2
 * ! 0 <= from_i, to_i < n
 * ! All pairs (from_i, to_i) are distinct.
 */

class Solution
{
public:
    std::vector<int> findSmallestSetOfVertices(int n, std::vector<std::vector<int>>& edges)
    {
        // count indegree of each node,
        // for the ith node, if indegree[i] = 0, it is in the final result
        std::vector<int> indegrees(n, 0);
        for (const auto& edge : edges) {
            indegrees[edge[1]]++;
        }
        std::vector<int> result;
        for (size_t i = 0; i < n; ++i) {
            if (indegrees[i] == 0) {
                result.push_back(i);
            }
        }
        return result;
    }
};