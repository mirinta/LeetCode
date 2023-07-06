#include <queue>
#include <unordered_map>
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
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites)
    {
        return approach2(numCourses, prerequisites);
    }

private:
    bool approach2(int n, std::vector<std::vector<int>>& prerequisites)
    {
        // Kahn's algorithm (topological sorting )
        std::vector<std::vector<int>> graph(n, std::vector<int>());
        std::vector<int> indgrees(n, 0);
        for (const auto& p : prerequisites) {
            graph[p[1]].push_back(p[0]);
            indgrees[p[0]]++;
        }
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (indgrees[i] == 0) {
                queue.push(i);
            }
        }
        int count = 0;
        while (!queue.empty()) {
            const int v = queue.front();
            queue.pop();
            count++;
            for (const auto& adj : graph[v]) {
                if (--indgrees[adj] == 0) {
                    queue.push(adj);
                }
            }
        }
        return count == n;
    }

    enum Color { White, Gray, Black };

    bool approach1(int n, std::vector<std::vector<int>>& prerequisites)
    {
        // cycle detection: DFS with colors
        std::vector<std::vector<int>> graph(n, std::vector<int>());
        for (const auto& p : prerequisites) {
            graph[p[1]].push_back(p[0]);
        }
        std::vector<Color> colors(n, White);
        for (int i = 0; i < n; ++i) {
            if (colors[i] == White && hasCycle(colors, i, graph))
                return false;
        }
        return true;
    }

    bool hasCycle(std::vector<Color>& colors, int start, const std::vector<std::vector<int>>& graph)
    {
        colors[start] = Gray;
        for (const auto& next : graph[start]) {
            if (colors[next] == Gray)
                return true;

            if (colors[next] == White && hasCycle(colors, next, graph))
                return true;
        }
        colors[start] = Black;
        return false;
    }
};