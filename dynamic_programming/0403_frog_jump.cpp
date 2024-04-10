#include <unordered_map>
#include <vector>

/**
 * A frog is crossing a river. The river is divided into some number of units, and at each unit,
 * there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the
 * water.
 *
 * Given a list of stones' positions (in units) in sorted ascending order, determine if the frog can
 * cross the river by landing on the last stone. Initially, the frog is on the first stone and
 * assumes the first jump must be 1 unit.
 *
 * If the frog's last jump was k units, its next jump must be either k - 1, k, or k + 1 units. The
 * frog can only jump in the forward direction.
 *
 * ! 2 <= stones.length <= 2000
 * ! 0 <= stones[i] <= 2^31 - 1
 * ! stones[0] == 0
 * ! stones is sorted in a strictly increasing order.
 */

class Solution
{
public:
    bool canCross(std::vector<int>& stones)
    {
        const int n = stones.size();
        memo = std::vector<std::vector<int>>(n, std::vector<int>(n, -1));
        for (int i = 0; i < n; ++i) {
            map[stones[i]] = i;
        }
        return dp(0, 0, stones);
    }

private:
    std::unordered_map<int, int> map;
    std::vector<std::vector<int>> memo;

    bool dp(int i, int k, const std::vector<int>& stones)
    {
        const int n = stones.size();
        if (i == n - 1)
            return true;

        if (memo[i][k] != -1)
            return memo[i][k];

        for (int offset = -1; offset <= 1; ++offset) {
            const int pos = stones[i] + k + offset;
            if (pos <= stones[i] || !map.count(pos))
                continue;

            if (dp(map[pos], pos - stones[i], stones))
                return memo[i][k] = true;
        }
        return memo[i][k] = false;
    }
};