#include <algorithm>
#include <vector>

/**
 * The distance of a pair of integers a and b is defined as the absolute difference between a and b.
 *
 * Given an integer array nums and an integer k, return the kth smallest distance among all the
 * pairs nums[i] and nums[j] where 0 <= i < j < nums.length.
 *
 * ! n == nums.length
 * ! 2 <= n <= 10^4
 * ! 0 <= nums[i] <= 10^6
 * ! 1 <= k <= n * (n - 1) / 2
 */

class Solution
{
public:
    int smallestDistancePair(std::vector<int>& nums, int k)
    {
        std::sort(nums.begin(), nums.end());
        int lo = 0;
        int hi = nums.back() - nums.front();
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            int count = 0;
            for (int left = 0, right = 0; right < nums.size(); ++right) {
                while (nums[right] - nums[left] > mid) {
                    left++;
                }
                count += right - left;
            }
            if (count >= k) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }
};