#include <algorithm>
#include <vector>

/**
 * Given a sorted integer array nums and an integer n, add/patch elements to the array such that any
 * number in the range [1, n] inclusive can be formed by the sum of some elements in the array.
 *
 * Return the minimum number of patches required.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 10^4
 * ! nums is sorted in ascending order.
 * ! 1 <= n <= 2^31 - 1
 */

class Solution
{
public:
    int minPatches(std::vector<int>& nums, int n)
    {
        // same as LC.2952
        // nums is already sorted in ascending order
        const int sz = nums.size();
        long long x = 0;
        int i = 0;
        int result = 0;
        while (x < n) {
            if (i < sz && (nums[i] == x + 1 || nums[i] <= x)) {
                x += nums[i];
                i++;
            } else {
                x = 2 * x + 1; // add an new integer x+1 to nums
                result++;
            }
        }
        return result;
    }
};