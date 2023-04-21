#include <vector>

/**
 * Given an integer array "nums" and an integer "k", split "nums" into "k" non-empty sub-arrays such
 * that the largest sum of any sub-array is minimized.
 *
 * Return the minimized largest sum of the split.
 *
 * A sub-array is contiguous part of the array.
 */

class Solution
{
public:
    int splitArray(std::vector<int>& nums, int k)
    {
        if (nums.empty() || k <= 0 || k > nums.size())
            return 0;

        // search range [maxValue, totalSum]
        int left = INT_MIN;
        int right = 0;
        for (const auto& i : nums) {
            right += i;
            left = std::max(left, i);
        }
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canSplit(nums, k, mid)) {
                right = mid - 1; // decrease upper bound
            } else {
                left = mid + 1;
            }
        }
        return right + 1;
    }

private:
    bool canSplit(const std::vector<int>& nums, int maxGroups, int maxSplitSum)
    {
        int groups = 1;
        int groupSum = 0;
        for (const auto& i : nums) {
            if (groupSum + i > maxSplitSum) {
                groupSum = i;
                groups++;
            } else {
                groupSum += i;
            }
        }
        return groups <= maxGroups;
    }
};