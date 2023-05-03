#include <vector>

/**
 * There are a total of "numCourses" courses you have to take, labeled from 0 to numCourse - 1. You
 * are given an array "prerequisites" where prerequisites[i] = [ai, bi] indicates that you must take
 * course bi first if you want to take course ai.
 *
 * For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
 *
 * Return true if you can finish all courses. Otherwise, return false.
 *
 * Example:
 * Input: numCourses = 2, prerequisites = [[1,0]]
 * Output: true
 * Explanation: There are a total of 2 courses to take. To take course 1 you should have finished
 * course 0. So it is possible.
 *
 * Example:
 * Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
 * Output: false
 * Explanation: There are a total of 2 courses to take.
 * To take course 1 you should have finished course 0, and to take course 0 you should also have
 * finished course 1. So it is impossible.
 *
 * ! 1 <= numCourses <= 2000
 * ! 0 <= prerequisites.length <= 5000
 * ! prerequisites[i].length == 2
 * ! 0 <= ai, bi < numCourses
 * ! All the pairs prerequisites[i] are unique.
 */

class Solution
{
public:
    bool canFinish(int numCourses, const std::vector<std::vector<int>>& prerequisites)
    {
        // build a graph
        std::vector<std::vector<int>> graph(numCourses, std::vector<int>{});
        for (const auto& p : prerequisites) {
            graph[p[1]].push_back(p[0]);
        }
        // DFS
        std::vector<bool> visited(numCourses, false);
        std::vector<bool> inPath(numCourses, false);
        bool isCyclic = false;
        for (size_t s = 0; s < graph.size(); ++s) {
            traverse(graph, s, visited, inPath, isCyclic);
        }
        return !isCyclic;
    }

private:
    void traverse(const std::vector<std::vector<int>>& graph, int source,
                  std::vector<bool>& visited, std::vector<bool>& inPath, bool& isCyclic)
    {
        if (inPath[source]) {
            isCyclic = true;
            return;
        }
        if (visited[source])
            return;

        visited[source] = true;
        inPath[source] = true;
        for (const auto& i : graph[source]) {
            traverse(graph, i, visited, inPath, isCyclic);
        }
        inPath[source] = false;
    }
};