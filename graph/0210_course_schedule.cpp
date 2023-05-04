#include <queue>
#include <vector>

/**
 * There are a total of "numCourses" courses you have to take, labeled from 0 to numCourse - 1. You
 * are given an array "prerequisites" where prerequisites[i] = [ai, bi] indicates that you must take
 * course bi first if you want to take course ai.
 *
 * For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
 *
 * Return the ordering of courses you should take to finish all courses. If there are many valid
 * answers, return any of them. If it is impossible to finish all courses, return an empty array.
 *
 * ! 1 <= numCourses <= 2000
 * ! 0 <= prerequisites.length <= numCourses * (numCourses - 1)
 * ! prerequisites[i].length == 2
 * ! 0 <= ai, bi < numCourses
 * ! ai != bi
 * ! All the pairs [ai, bi] are distinct.
 */

class Solution
{
public:
    std::vector<int> findOrder(int numCourses, const std::vector<std::vector<int>>& prerequisites)
    {
        // build graph
        std::vector<std::vector<int>> graph(numCourses, std::vector<int>{});
        for (const auto& p : prerequisites) {
            graph[p[1]].push_back(p[0]); // bi -> [ai, ...]
        }
        // version 1: DFS
        // visited.resize(numCourses, false);
        // inPath.resize(numCourses, false);
        // result.clear();
        // hasCycle = false;
        // for (size_t i = 0; i < graph.size(); ++i) {
        //     traverse(graph, i);
        // }
        // if (hasCycle)
        //     return {};

        // std::reverse(result.begin(), result.end());
        // return result;
        // version 2: BFS
        std::vector<int> indegrees(numCourses, 0);
        for (const auto& p : prerequisites) {
            indegrees[p[0]]++;
        }
        std::queue<int> queue;
        for (size_t i = 0; i < indegrees.size(); ++i) {
            if (indegrees[i] == 0) {
                queue.push(i);
            }
        }
        std::vector<int> result;
        int count = 0;
        while (!queue.empty()) {
            const auto s = queue.front();
            queue.pop();
            result.push_back(s);
            count++;
            for (const auto& i : graph[s]) {
                if (--indegrees[i] == 0) {
                    queue.push(i);
                }
            }
        }
        if (count != numCourses)
            return {};

        return result;
    }

private:
    std::vector<bool> visited;
    std::vector<bool> inPath;
    std::vector<int> result;
    bool hasCycle = false;

    void traverse(const std::vector<std::vector<int>>& graph, int source)
    {
        if (inPath[source]) {
            hasCycle = true;
            return;
        }
        if (visited[source])
            return;

        visited[source] = true;
        inPath[source] = true;
        for (const auto& i : graph[source]) {
            traverse(graph, i);
        }
        inPath[source] = false;
        result.push_back(source);
    }
};