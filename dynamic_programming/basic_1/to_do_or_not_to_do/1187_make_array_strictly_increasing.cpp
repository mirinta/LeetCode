#include <algorithm>
#include <vector>

/**
 * Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero)
 * needed to make arr1 strictly increasing.
 *
 * In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do
 * the assignment arr1[i] = arr2[j].
 *
 * If there is no way to make arr1 strictly increasing, return -1.
 *
 * ! 1 <= arr1.length, arr2.length <= 2000
 * ! 0 <= arr1[i], arr2[i] <= 10^9
 *
 * Example:
 * Input: arr1 = [1,5,3,6,7], arr2 = [4,3,1]
 * Output: 2
 * Explanation: Replace 5 with 3 and then replace 3 with 4. arr1 = [1, 3, 4, 6, 7].
 *
 * Example:
 * Input: arr1 = [1,5,3,6,7], arr2 = [1,6,3,3]
 * Output: -1
 * Explanation: You can't make arr1 strictly increasing.
 */

class Solution
{
public:
    int makeArrayIncreasing(std::vector<int>& arr1, std::vector<int>& arr2)
    {
        std::sort(arr2.begin(), arr2.end());
        const auto m = arr1.size();
        const auto n = arr2.size(); // at most arr2.size() operations
        // dp[i][k] = the min value of arr1[i] after using k operations to make arr1[0:i) strictly
        // increasing
        // - to exercise or not to exercise some kind of rights (swapping elements)
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, INT_MAX));
        dp[0][0] = INT_MIN;
        for (int i = 1; i <= m; ++i) {
            for (int k = 0; k <= n; ++k) {
                // case1: no swapping
                if (dp[i - 1][k] < arr1[i - 1]) {
                    dp[i][k] = std::min(dp[i][k], arr1[i - 1]);
                }
                // case2: swapping
                if (k < 1)
                    continue;

                auto iter = std::upper_bound(arr2.begin(), arr2.end(), dp[i - 1][k - 1]);
                if (iter != arr2.end()) {
                    dp[i][k] = std::min(dp[i][k], *iter);
                }
            }
        }
        int result = INT_MAX;
        for (int k = 0; k <= n; ++k) {
            if (dp[m][k] != INT_MAX) {
                result = std::min(result, k);
            }
        }
        return result == INT_MAX ? -1 : result;
    }
};