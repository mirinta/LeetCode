#include <queue>
#include <unordered_map>
#include <vector>

/**
 * On a campus represented on the X-Y plane, there are n workers and m bikes, with n <= m.
 *
 * You are given an array workers of length n where workers[i] = [xi, yi] is the position of the ith
 * worker. You are also given an array bikes of length m where bikes[j] = [xj, yj] is the position
 * of the jth bike. All the given positions are unique.
 *
 * Assign a bike to each worker. Among the available bikes and workers, we choose the (workeri,
 * bikej) pair with the shortest Manhattan distance between each other and assign the bike to that
 * worker.
 *
 * If there are multiple (workeri, bikej) pairs with the same shortest Manhattan distance, we choose
 * the pair with the smallest worker index. If there are multiple ways to do that, we choose the
 * pair with the smallest bike index. Repeat this process until there are no available workers.
 *
 * Return an array answer of length n, where answer[i] is the index (0-indexed) of the bike that the
 * ith worker is assigned to.
 *
 * The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y
 * - p2.y|.
 *
 * ! n == workers.length
 * ! m == bikes.length
 * ! 1 <= n <= m <= 1000
 * ! workers[i].length == bikes[j].length == 2
 * ! 0 <= xi, yi < 1000
 * ! 0 <= xj, yj < 1000
 * ! All worker and bike locations are unique.
 */

class Solution
{
public:
    std::vector<int> assignBikes(std::vector<std::vector<int>>& workers,
                                 std::vector<std::vector<int>>& bikes)
    {
        const int n = workers.size();
        const int m = bikes.size();
        std::priority_queue<Tuple, std::vector<Tuple>, std::greater<>> pq; // min heap
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                pq.emplace(manhattan(workers[i], bikes[j]), i, j);
            }
        }
        std::vector<bool> usedBikes(m, false);
        std::unordered_map<int, int> map; // worker to bike
        while (map.size() != n) {
            while (!pq.empty()) {
                const auto [dist, worker, bike] = pq.top();
                if (!map.count(worker) && !usedBikes[bike])
                    break;

                pq.pop();
            }
            const auto [dist, worker, bike] = pq.top();
            pq.pop();
            map[worker] = bike;
            usedBikes[bike] = true;
            ;
        }
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = map[i];
        }
        return result;
    }

private:
    using Tuple = std::tuple<int, int, int>;

    int manhattan(const std::vector<int>& workerCoords, const std::vector<int>& bikeCoords)
    {
        return std::abs(workerCoords[0] - bikeCoords[0]) +
               std::abs(workerCoords[1] - bikeCoords[1]);
    }
};
