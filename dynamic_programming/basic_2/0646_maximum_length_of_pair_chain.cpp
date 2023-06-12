#include <algorithm>
#include <vector>

/**
 * You are given an array of n pairs "pairs" where pairs[i] = [left_i, right_i] and left_i <
 * right_i.
 *
 * A pair p2 = [c, d] follows a pair p1 = [a, b] if b < c. A chain of pairs can be formed in this
 * fashion.
 *
 * Return the length longest which can be formed.
 *
 * You do not need to use up all the given intervals. You can select pairs in any order.
 *
 * Example:
 * Input: pairs = [[1, 2], [2, 3], [3, 4]]
 * Output: 2
 * Explanation: The longest chain is [1, 2] -> [3, 4].
 *
 * ! n == pairs.length
 * ! 1 <= n <= 1000
 * ! -1000 <= left_i < right_i <= 1000
 */

class Solution
{
public:
    int findLongestChain(std::vector<std::vector<int>>& pairs) { return approach2(pairs); }

private:
    // DP: LIS
    int approach1(std::vector<std::vector<int>>& pairs)
    {
        if (pairs.size() <= 1)
            return pairs.size();

        std::sort(pairs.begin(), pairs.end(),
                  [](const auto& pair1, const auto& pair2) { return pair1[0] < pair2[0]; });
        // dp[i] = length of the longest LIS that ends with pairs[i]
        const auto n = pairs.size();
        std::vector<int> dp(n, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (pairs[i][0] > pairs[j][1]) {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
        }
        int result = INT_MIN;
        for (const auto& val : dp) {
            result = std::max(result, val);
        }
        return result;
    }

    // Greedy
    // sort by second coordinates
    // 1-2          <= count = 1
    //   2-3
    //     3-4      <= count = 2
    // --------------
    // 1-2          <= count = 1
    //     4-5      <= count = 2
    //         7-8  <= count = 3
    int approach2(std::vector<std::vector<int>>& pairs)
    {
        if (pairs.size() <= 1)
            return pairs.size();

        std::sort(pairs.begin(), pairs.end(),
                  [](const auto& pair1, const auto& pair2) { return pair1[1] < pair2[1]; });
        int result = 0;
        int cur = INT_MIN;
        for (const auto& pair : pairs) {
            if (pair[0] > cur) {
                cur = pair[1];
                result++;
            }
        }
        return result;
    }
};
