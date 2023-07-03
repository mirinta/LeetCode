#include <stack>
#include <unordered_set>
#include <vector>

/**
 * There are n rooms labeled from 0 to n - 1 and all the rooms are locked except for room 0. Your
 * goal is to visit all the rooms. However, you cannot enter a locked room without having its key.
 *
 * When you visit a room, you may find a set of distinct keys in it. Each key has a number on it,
 * denoting which room it unlocks, and you can take all of them with you to unlock the other rooms.
 *
 * Given an array rooms where rooms[i] is the set of keys that you can obtain if you visited room i,
 * return true if you can visit all the rooms, or false otherwise.
 *
 * ! n == rooms.length
 * ! 2 <= n <= 1000
 * ! 0 <= rooms[i].length <= 1000
 * ! 1 <= sum(rooms[i].length) <= 3000
 * ! 0 <= rooms[i][j] < n
 * ! All the values of rooms[i] are unique.
 */

class Solution
{
public:
    bool canVisitAllRooms(std::vector<std::vector<int>>& rooms)
    {
        std::unordered_set<int> visited;
        visited.insert(0);
        std::stack<int> stack;
        stack.push(0);
        while (!stack.empty()) {
            const int i = stack.top();
            stack.pop();
            for (const auto& j : rooms[i]) {
                if (visited.count(j))
                    continue;

                visited.insert(j);
                stack.push(j);
            }
        }
        return visited.size() == rooms.size();
    }

private:
    // DFS, recursion
    bool approach1(std::vector<std::vector<int>>& rooms)
    {
        std::unordered_set<int> visited;
        visited.insert(0);
        dfs(visited, 0, rooms);
        return visited.size() == rooms.size();
    }

    void dfs(std::unordered_set<int>& visited, int current,
             const std::vector<std::vector<int>>& rooms)
    {
        for (const auto& i : rooms[current]) {
            if (visited.count(i))
                continue;

            visited.insert(i);
            dfs(visited, i, rooms);
        }
    }
};