#include <queue>
#include <vector>

/**
 * Given an array of non-negative integers arr, you are initially positioned at start index of the
 * array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach
 * to any index with value 0.
 *
 * Notice that you can not jump outside of the array at any time.
 *
 * ! 1 <= arr.length <= 5 * 10^4
 * ! 0 <= arr[i] < arr.length
 * ! 0 <= start < arr.length
 */

class Solution
{
public:
    // BFS, time O(N), space O(N)
    bool canReach(std::vector<int>& arr, int start)
    {
        const int n = arr.size();
        std::vector<int> visited(n, false);
        visited[start] = true;
        std::queue<int> queue;
        queue.push(start);
        const std::vector<int> factors{1, -1};
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto v = queue.front();
                queue.pop();
                if (arr[v] == 0)
                    return true;

                for (const auto& f : factors) {
                    const int adj = v + f * arr[v];
                    if (adj < 0 || adj >= n || visited[adj])
                        continue;

                    visited[adj] = true;
                    queue.push(adj);
                }
            }
        }
        return false;
    }
};