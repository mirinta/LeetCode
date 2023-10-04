#include <algorithm>
#include <vector>

/**
 * Given an integer array nums of length n and an integer target, find three integers in nums such
 * that the sum is closest to target.
 *
 * Return the sum of the three integers.
 *
 * You may assume that each input would have exactly one solution.
 *
 * ! 3 <= nums.length <= 500
 * ! -1000 <= nums[i] <= 1000
 * ! -10^4 <= target <= 10^4
 */

class Solution
{
public:
    int threeSumClosest(std::vector<int>& nums, int target)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int minAbsDiff = INT_MAX;
        int result = 0;
        auto update = [&minAbsDiff, &result](int sum, int target) {
            if (const int diff = std::abs(sum - target); diff < minAbsDiff) {
                minAbsDiff = diff;
                result = sum;
            }
        };
        for (int i = 0; i < n - 2; ++i) {
            if (i >= 1 && nums[i] == nums[i - 1])
                continue; // skip same nums[i]

            // optimization 1
            if (const int sum = nums[i] + nums[i + 1] + nums[i + 2]; sum > target) {
                update(sum, target);
                break;
            }
            // optimization 2
            if (const int sum = nums[i] + nums[n - 1] + nums[n - 2]; sum < target) {
                update(sum, target);
                continue;
            }
            // two-pointers:
            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                const int sum = nums[i] + nums[left] + nums[right];
                if (sum == target)
                    return sum;

                update(sum, target);
                if (sum > target) {
                    right--;
                } else {
                    left++;
                }
            }
        }
        return result;
    }
};