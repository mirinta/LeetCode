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
    int longestOnes(std::vector<int>& nums, int k)
    {
        int left = 0;
        int right = 0;
        for (; right < nums.size(); ++right) {
            if (nums[right] == 0) {
                k--;
            }
            if (k < 0 && nums[left++] == 0) {
                k++;
            }
        }
        return right - left;
    }
};