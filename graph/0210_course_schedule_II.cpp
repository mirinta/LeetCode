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
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites)
    {
        return approach1(numCourses, prerequisites);
    }

private:
    std::vector<int> approach2(int numCourses, std::vector<std::vector<int>>& prerequisites)
    {
        // topological sorting, Kahn's algorithm
        std::vector<std::vector<int>> graph(numCourses, std::vector<int>());
        std::vector<int> indegrees(numCourses, 0);
        for (const auto& p : prerequisites) {
            graph[p[1]].push_back(p[0]);
            indegrees[p[0]]++;
        }
        std::queue<int> queue;
        for (int i = 0; i < numCourses; ++i) {
            if (indegrees[i] == 0) {
                queue.push(i);
            }
        }
        std::vector<int> result;
        while (!queue.empty()) {
            const int v = queue.front();
            queue.pop();
            result.push_back(v);
            for (const auto& adj : graph[v]) {
                if (--indegrees[adj] == 0) {
                    queue.push(adj);
                }
            }
        }
        if (result.size() != numCourses)
            return {};

        return result;
    }

    enum Color { White, Gray, Black };

    std::vector<int> approach1(int numCourses, std::vector<std::vector<int>>& prerequisites)
    {
        std::vector<std::vector<int>> graph(numCourses, std::vector<int>());
        for (const auto& p : prerequisites) {
            graph[p[1]].push_back(p[0]);
        }
        std::vector<Color> colors(numCourses, White);
        std::vector<int> result;
        for (int i = 0; i < numCourses; ++i) {
            if (colors[i] == White && hasCycle(colors, result, i, graph))
                return {};
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    bool hasCycle(std::vector<Color>& colors, std::vector<int>& result, int start,
                  const std::vector<std::vector<int>>& graph)
    {
        colors[start] = Gray;
        for (const auto& next : graph[start]) {
            if (colors[next] == Gray)
                return true;

            if (colors[next] == White && hasCycle(colors, result, next, graph))
                return true;
        }
        colors[start] = Black;
        result.push_back(start);
        return false;
    }
};
