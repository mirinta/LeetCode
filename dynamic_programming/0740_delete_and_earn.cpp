#include <unordered_map>
#include <vector>

/**
 * You are given an integer array "nums". You want to maximize the number of points you get by
 * performing the following operation any number of times:
 *
 * - Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you must delete every
 * element equal to nums[i]-1 and every element equal to nums[i]+1.
 *
 * Return the maximum number of points you can earn by applying the above operation some number of
 * times.
 */

class Solution
{
public:
    int deleteAndEarn(std::vector<int>& nums)
    {
        // nums = [2, 2, 3, 3, 3, 4]
        // - number of 2 = 2, if we delete 2, we earn at least 2 * 2 = 4 points
        // - number of 3 = 3, if we delete 3, we earn at least 3 * 3 = 9 points
        // - number of 4 = 1, if we delete 4, we earn at least 4 * 1 = 4 points
        // construct an array: arr[i] = min points we earn if we delete i
        // index:  0  1  2  3  4
        // value:  0  0  4  9  4
        // if we pick index i, then index of i+1 and i-1 can't be pickd
        // this is similar to the House Robber Problem, see LC 198
        std::unordered_map<int, int> map; // map[i] = nums[i] * number of nums[i]
        int maxNum = INT_MIN;
        for (const auto& val : nums) {
            map[val] += val;
            maxNum = std::max(maxNum, val);
        }
        // dp[i] = max val of robbing house[i:end]
        std::vector<int> dp(maxNum + 1); // n = maxNum + 1
        // base cases:
        // - dp[n-1], only one choice
        // - dp[n-2], only two choices, pick the one with max value
        dp[maxNum] = map[maxNum];
        dp[maxNum - 1] = std::max(map[maxNum], map[maxNum - 1]);
        for (int i = maxNum - 2; i >= 0; --i) {
            dp[i] = std::max(dp[i + 1], dp[i + 2] + map[i]);
        }
        return dp[0];
    }
};