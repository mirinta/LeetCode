#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed integer array nums and an integer p. Find p pairs of indices of nums
 * such that the maximum difference amongst all the pairs is minimized. Also, ensure no index
 * appears more than once amongst the p pairs.
 *
 * Note that for a pair of elements at the index i and j, the difference of this pair is |nums[i] -
 * nums[j]|, where |x| represents the absolute value of x.
 *
 * Return the minimum maximum difference among all p pairs. We define the maximum of an empty set to
 * be zero.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^9
 * ! 0 <= p <= (nums.length)/2
 */

class Solution
{
public:
    int minimizeMax(std::vector<int>& nums, int p)
    {
        std::sort(nums.begin(), nums.end());
        // search the maximum difference among pairs
        int lo = 0;
        int hi = nums.back() - nums.front();
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, nums, p)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    // nums is sorted in ascending order
    // #NOTE# no index appears more than once among the pairs
    bool isValid(int maxDiff, const std::vector<int>& nums, int minPairs)
    {
        int count = 0;
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i + 1] - nums[i] <= maxDiff) {
                count++;
                i++;
            }
        }
        return count >= minPairs;
    }
};