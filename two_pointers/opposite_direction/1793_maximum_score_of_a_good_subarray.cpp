#include <vector>

/**
 * You are given an array of integers nums (0-indexed) and an integer k.
 *
 * The score of a subarray (i, j) is defined as min(nums[i], nums[i+1], ..., nums[j]) * (j - i + 1).
 * A good subarray is a subarray where i <= k <= j.
 *
 * Return the maximum possible score of a good subarray.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 2 * 10^4
 * ! 0 <= k < nums.length
 */

class Solution
{
public:
    int maximumScore(std::vector<int>& nums, int k)
    {
        // k is fixed
        // X X i X X k X X j X X
        //     |     ^     |
        //    left        right
        // two pointers:
        // - "left" goes from right to left
        // - "right" goes from left to right
        // - both of them star at k, so the min value is nums[k] at the beginning
        // - if min is maintained, we expand the two pointers to make the length as long as possible
        // - otherwise, update min = the max value between nums[left] and [right]
        const int n = nums.size();
        int left = k;
        int right = k;
        int min = nums[k];
        int result = INT_MIN;
        while (left >= 0 || right < n) {
            while (left >= 0 && nums[left] >= min) {
                left--;
            }
            while (right < n && nums[right] >= min) {
                right++;
            }
            result = std::max(result, min * (right - left - 1));
            min = std::max(left < 0 ? INT_MIN : nums[left], right >= n ? INT_MIN : nums[right]);
        }
        return result;
    }
};