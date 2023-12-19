#include <deque>
#include <vector>

/**
 * You are given a 0-indexed integer array nums.
 *
 * You can perform any number of operations, where each operation involves selecting a subarray of
 * the array and replacing it with the sum of its elements. For example, if the given array is
 * [1,3,5,6] and you select subarray [3,5] the array will convert to [1,8,6].
 *
 * Return the maximum length of a non-decreasing array that can be made after applying operations.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 */

class Solution
{
public:
    int findMaximumLength(std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i] = max length of non-decreasing array that can be made after applying operations on
        // nums[0:i) last[i] = last value of the modified array of nums[0:i)
        // X X X X j X X X X X X i
        //           |<--merge-->|
        // we want to find the largest index j such that presum[i] - presum[j] >= last[j],
        // then dp[i] = dp[j] + 1 and last[i] = presum[i] - presum[j]
        std::vector<long long> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        std::vector<int> dp(n + 1, 0);
        std::vector<int> last(n + 1, 0);
        std::deque<std::pair<int, long long>> deque; // <j, presum[j] + last[j]>
        for (int i = 1, j = 0; i <= n; ++i) {
            while (!deque.empty() && presum[i] >= deque.front().second) {
                j = deque.front().first;
                deque.pop_front();
            }
            dp[i] = dp[j] + 1;
            last[i] = presum[i] - presum[j];
            while (!deque.empty() && deque.back().second >= presum[i] + last[i]) {
                deque.pop_back();
            }
            deque.emplace_back(i, presum[i] + last[i]);
        }
        return dp[n];
    }
};