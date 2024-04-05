#include <algorithm>
#include <set>
#include <vector>

/**
 * You have n tasks and m workers. Each task has a strength requirement stored in a 0-indexed
 * integer array tasks, with the ith task requiring tasks[i] strength to complete. The strength of
 * each worker is stored in a 0-indexed integer array workers, with the jth worker having workers[j]
 * strength. Each worker can only be assigned to a single task and must have a strength greater than
 * or equal to the task's strength requirement (i.e., workers[j] >= tasks[i]).
 *
 * Additionally, you have pills magical pills that will increase a worker's strength by strength.
 * You can decide which workers receive the magical pills, however, you may only give each worker at
 * most one magical pill.
 *
 * Given the 0-indexed integer arrays tasks and workers and the integers pills and strength, return
 * the maximum number of tasks that can be completed.
 *
 * ! n == tasks.length
 * ! m == workers.length
 * ! 1 <= n, m <= 5 * 10^4
 * ! 0 <= pills <= m
 * ! 0 <= tasks[i], workers[j], strength <= 10^9
 */

class Solution
{
public:
    int maxTaskAssign(std::vector<int>& tasks, std::vector<int>& workers, int pills, int strength)
    {
        std::sort(tasks.begin(), tasks.end());
        std::sort(workers.begin(), workers.end());
        int lo = 0;
        int hi = tasks.size();
        while (lo < hi) {
            const int mid = hi - (hi - lo) / 2;
            if (isValid(mid, tasks, workers, pills, strength)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return hi;
    }

private:
    // check if it is possible to complete k tasks
    // greedy: choose the k strongest workers to finish the k easiest tasks
    bool isValid(int k, const std::vector<int>& tasks, const std::vector<int>& workers, int pills,
                 int strength)
    {
        if (k > tasks.size() || k > workers.size())
            return false;

        std::multiset<int> set(workers.end() - k, workers.end());
        for (int i = k - 1; i >= 0; --i) {
            if (*set.rbegin() >= tasks[i]) {
                set.erase(std::prev(set.end()));
                continue;
            }
            if (pills == 0)
                return false;

            // find the weakest worker such that his strength + pill strength >= tasks[i]
            auto iter = set.lower_bound(tasks[i] - strength);
            if (iter == set.end())
                return false;

            set.erase(iter);
            pills--;
        }
        return true;
    }
};