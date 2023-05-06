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
    // #combinations of array with size N = 2^(N-1)
    // arr = [1]
    // - combinations: [1]
    // - #combinations = 1
    // arr = [1, 2]
    // - combinations: [1], [1, 2]
    // - #combinations = 3
    // arr = [1, 2, 3]
    // - combinations: [1], [1, 2], [1, 2, 3], [2, 3]
    // - #combinations = 4
    int numSubseq(std::vector<int>& nums, int target)
    {
        constexpr int mod = 1e9 + 7;
        // store values
        std::vector<int> pow2(nums.size(), 1);
        for (size_t i = 1; i < pow2.size(); ++i) {
            pow2[i] = pow2[i - 1] << 1;
            if (pow2[i] >= mod) {
                pow2[i] -= mod;
            }
        }
        // sort in non-decreasing order
        std::sort(nums.begin(), nums.end());
        int result = 0;
        int low = 0;
        int high = nums.size() - 1;
        // binary search
        while (low <= high) {
            if (nums[low] + nums[high] > target) {
                high--;
            } else {
                result += pow2[high - low++];
                if (result >= mod) {
                    result -= mod;
                }
            }
        }
        return result;
    }
};