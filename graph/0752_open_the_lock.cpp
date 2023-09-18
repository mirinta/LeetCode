#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: 0, 1, 2, 3, 4,
 * 5, 6, 7, 8, 9. The wheels can rotate freely and wrap around: for example we can turn 9 to be 0,
 * or 0 to be 9. Each move consists of turning one wheel one slot.
 *
 * The lock initially starts at 0000, a string representing the state of the 4 wheels.
 *
 * You are given a list of "deadends" dead ends, meaning if the lock display any of these codes, the
 * wheels of the lock will stop turning and you will be unable to open it.
 *
 * Given a "target" representing the value of the wheels that will unlock the lock, return the
 * minimum total number of turns required to open the lock, or -1 if it is impossible.
 *
 * ! Constraints:
 * ! - deadends[i].length == 4
 * ! - target.length == 4
 * ! - "target" will not be in the list "deadends".
 * ! - "target" and "deadends[i]" consist of digits only.
 */

class Solution
{
public:
    int openLock(std::vector<std::string>& deadends, std::string target)
    {
        std::unordered_set<std::string> prohibitions(deadends.begin(), deadends.end());
        std::unordered_set<std::string> visited;
        visited.insert("0000");
        std::queue<std::string> queue;
        queue.emplace("0000");
        int steps = 0;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto current = queue.front();
                queue.pop();
                if (current == target)
                    return steps;

                if (prohibitions.count(current))
                    continue;

                for (int i = 0; i < 4; ++i) {
                    for (const auto& direction : {1, -1}) {
                        auto rotated = rotateIthWheel(i, direction, current);
                        if (visited.count(rotated))
                            continue;

                        queue.push(rotated);
                        visited.insert(std::move(rotated));
                    }
                }
            }
            steps++;
        }
        return -1;
    }

private:
    // direction = -1 or 1
    std::string rotateIthWheel(int i, int direction, const std::string& lock)
    {
        std::string result(lock);
        result[i] = (result[i] - '0' + direction + 10) % 10 + '0';
        return result;
    }
};
