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
    int openLock(const std::vector<std::string>& deadends, const std::string& target)
    {
        // record all deadends
        std::unordered_set<std::string> prohibitions;
        for (const auto& s : deadends) {
            prohibitions.insert(s);
        }
        // record if a candidate is already checked
        std::unordered_set<std::string> checked;
        checked.insert("0000");
        // BFS
        std::queue<std::string> queue;
        queue.push("0000");
        int result = 0;
        while (!queue.empty()) {
            const auto size = queue.size();
            for (size_t i = 0; i < size; ++i) {
                const auto s = queue.front();
                queue.pop();
                if (prohibitions.count(s))
                    continue;

                if (s == target)
                    return result;

                for (size_t k = 0; k < 4; ++k) {
                    const auto up = spinUpKthWheel(s, k);
                    if (!checked.count(up)) {
                        checked.insert(up);
                        queue.push(up);
                    }
                    const auto down = spinDownKthWheel(s, k);
                    if (!checked.count(down)) {
                        checked.insert(down);
                        queue.push(down);
                    }
                }
            }
            result++;
        }
        return -1;
    }

private:
    std::string spinUpKthWheel(const std::string& s, int k)
    {
        // 0 to 1, 1 to 2, ..., 9 to 0.
        // k is 0-indexed, 0 <= k <= 3, s.size() == 4
        std::string result(s);
        const auto& val = result[k];
        result[k] = val == '9' ? '0' : val + 1;
        return result;
    }

    std::string spinDownKthWheel(const std::string& s, int k)
    {
        // 0 to 9, 1 to 0, ..., 9 to 8.
        // k is 0-indexed, 0 <= k <= 3, s.size() == 4
        std::string result(s);
        const auto& val = result[k];
        result[k] = val == '0' ? '9' : val - 1;
        return result;
    }
};