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
        std::unordered_map<int, int> map; // stone position to stone index
        for (int i = 0; i < n; ++i) {
            map[stones[i]] = i;
        }
        // dp[i][j] = whether the frog can reach stones[i] with j jumps last time
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
        dp[0][0] = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!dp[i][j])
                    continue;

                for (int jumps = j - 1; jumps <= j + 1; ++jumps) {
                    if (jumps < 0)
                        continue;

                    const int pos = jumps + stones[i];
                    if (map.count(pos)) {
                        dp[map[pos]][jumps] = true;
                    }
                }
            }
        }
        for (const auto& canReachLastStone : dp[n - 1]) {
            if (canReachLastStone)
                return true;
        }
        return false;
    }
};