#include <queue>
#include <vector>

/**
 * A company has "n" employees with a unique ID for each employee from 0 to n - 1. The head of the
 * company is the one with "headID".
 *
 * Each employee has one direct manager given in the manager array where manager[i] is the direct
 * manager of the ith employee, manager[headID] = -1. Also, it is guaranteed that the subordination
 * relationships have a tree structure.
 *
 * The head of the company wants to inform all the company employees of an urgent piece of news. He
 * will inform his direct subordinates, and they will inform there subordinates, and so on until all
 * employees know about the urgent news.
 *
 * The ith employee needs informTime[i] minutes to inform all of this direct subordinates (i.e.,
 * After informTime[i] minutes, all his direct subordinates can start spreading the news).
 *
 * Return the number of minutes needed to inform all the employees about the urgent news.
 *
 * ! 1 <= n <= 105
 * ! 0 <= headID < n
 * ! manager.length == n
 * ! 0 <= manager[i] < n
 * ! manager[headID] == -1
 * ! informTime.length == n
 * ! 0 <= informTime[i] <= 1000
 * ! informTime[i] == 0 if employee i has no subordinates.
 * ! It is guaranteed that all the employees can be informed.
 */

class Solution
{
public:
    int numOfMinutes(int n, int headID, const std::vector<int>& manager,
                     const std::vector<int>& informTime)
    {
        std::vector<std::vector<int>> tree(n, std::vector<int>{}); // director->{employees}
        for (int i = 0; i < n; ++i) {
            const auto& director = manager[i] < 0 ? headID : manager[i];
            if (director == i)
                continue;

            tree[director].push_back(i);
        }
        // return dfs(headID, tree, informTime);
        return bfs(headID, tree, informTime);
    }

private:
    int dfs(int director, const std::vector<std::vector<int>>& tree,
            const std::vector<int>& informTime)
    {
        int result = 0;
        for (const auto& employee : tree[director]) {
            result = std::max(result, informTime[director] + dfs(employee, tree, informTime));
        }
        return result;
    }

    int bfs(int headID, const std::vector<std::vector<int>>& tree,
            const std::vector<int>& informTime)
    {
        int result = 0;
        std::queue<std::pair<int, int>> queue;
        queue.push({headID, 0});
        while (!queue.empty()) {
            const auto [director, time] = queue.front();
            queue.pop();
            result = std::max(time, result);
            for (const auto& employee : tree[director]) {
                queue.push({employee, time + informTime[director]});
            }
        }
        return result;
    }
};