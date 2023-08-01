#include <algorithm>
#include <vector>

/**
 * You are given an array of integers "nums" and an integer "target".
 *
 * Return the number of non-empty subsequences of "nums" such that the sum of the minimum and
 * maximum element on it is less or equal to target. Since the answer may be too large, return it
 * module 10^9 + 7.
 *
 * Example:
 * Input: nums = [3, 5, 6, 7], target = 9
 * Output: 4
 * Explanation: There are 4 subsequences that satisfy the condition.
 * - [3] -> min value + max value = 6 <= 9
 * - [3, 5] -> min value + max value = 8 <= 9
 * - [3, 5, 6] -> min value + max value = 9 <= 9
 * - [3, 6] -> min value + max value = 9 <= 9
 */

class Solution
{
public:
    int numSubseq(std::vector<int>& nums, int target)
    {
        constexpr int kMod = 1e9 + 7;
        const int n = nums.size();
        // number of subsequences = 2^n
        // number of non-empty subsequences = 2^n - 1
        std::vector<int> pow2(n, 1);
        for (int i = 1; i < n; ++i) {
            pow2[i] = (pow2[i - 1] << 1) % kMod;
        }
        std::sort(nums.begin(), nums.end());
        int lo = 0;
        int hi = n - 1;
        int result = 0;
        while (lo <= hi) {
            if (nums[lo] + nums[hi] > target) {
                hi--;
            } else {
                // lo [lo+1 ... hi]
                // fix lo, each of the remaining numbers has 2 choices: pick or not pick
                // i.e., num of subsequences = 2^(hi-lo)
                result = (result + pow2[hi - lo]) % kMod;
                lo++;
            }
        }
        return result;
    }
};