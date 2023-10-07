#include <vector>

/**
 * Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the
 * array if you can flip at most k 0's.
 *
 * ! 1 <= nums.length <= 10^5
 * ! nums[i] is either 0 or 1.
 * ! 0 <= k <= nums.length
 */

class Solution
{
public:
    // sliding window, time O(N), space O(1)
    int longestOnes(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            if (nums[right] == 0) {
                k--;
            }
            while (k < 0) {
                if (nums[left] == 0) {
                    k++;
                }
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};
