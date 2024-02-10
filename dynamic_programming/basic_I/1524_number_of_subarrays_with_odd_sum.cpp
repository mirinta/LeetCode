#include <array>
#include <vector>

/**
 * Given an array of integers arr, return the number of subarrays with an odd sum.
 *
 * Since the answer can be very large, return it modulo 109 + 7.
 *
 * ! 1 <= arr.length <= 10^5
 * ! 1 <= arr[i] <= 100
 */

class Solution
{
public:
    int numOfSubarrays(std::vector<int>& arr) { return approach2(arr); }

private:
    static constexpr int kMod = 1e9 + 7;

    // DP with space optimization, TC = O(N), SC = O(1)
    int approach2(const std::vector<int>& arr)
    {
        const int n = arr.size();
        int odd = arr[0] & 1;
        int even = 1 - odd;
        int result = odd;
        for (int i = 1; i < n; ++i) {
            if (arr[i] & 1) {
                std::swap(odd, even);
                odd++;
            } else {
                even++;
            }
            result = (result + odd) % kMod;
        }
        return result;
    }

    // DP, TC = O(N), SC = O(N)
    int approach1(const std::vector<int>& arr)
    {
        // dp[i][0] = num of subarrays of nums[0:i] ending at nums[i] with an even sum
        // dp[i][1] = num of subarrays of nums[0:i] ending at nums[i] with an odd sum
        const int n = arr.size();
        std::vector<std::array<int, 2>> dp(n, {0, 0});
        dp[0][arr[0] & 1] = 1;
        int result = dp[0][1];
        for (int i = 1; i < n; ++i) {
            if (arr[i] & 1) {
                dp[i][0] = dp[i - 1][1];
                dp[i][1] = 1 + dp[i - 1][0];
            } else {
                dp[i][0] = 1 + dp[i - 1][0];
                dp[i][1] = dp[i - 1][1];
            }
            result = (result + dp[i][1]) % kMod;
        }
        return result;
    }
};