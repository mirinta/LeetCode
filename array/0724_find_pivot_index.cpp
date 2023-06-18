#include <vector>

/**
 * Given an array of integers nums, calculate the pivot index of this array.
 *
 * The pivot index is the index where the sum of all the numbers strictly to the left of the index
 * is equal to the sum of all the numbers strictly to the index's right.
 *
 * If the index is on the left edge of the array, then the left sum is 0 because there are no
 * elements to the left. This also applies to the right edge of the array.
 *
 * Return the leftmost pivot index. If no such index exists, return -1.
 *
 * ! 1 <= nums.length <= 10^4
 * ! -1000 <= nums[i] <= 1000
 *
 * ! This question is the same as LC 1991.
 */

class Solution
{
public:
    int pivotIndex(const std::vector<int>& nums)
    {
        if (nums.empty())
            return -1;

        if (nums.size() == 1)
            return 0;

        int totalSum = 0;
        for (const auto& val : nums) {
            totalSum += val;
        }
        int leftPartSum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (leftPartSum == totalSum - nums[i] - leftPartSum)
                return i;

            leftPartSum += nums[i];
        }
        return -1;
    }

private:
    int approach1(const std::vector<int>& nums)
    {
        if (nums.empty())
            return -1;

        if (nums.size() == 1)
            return 0;

        std::vector<int> preSum(nums.size() + 1, 0);
        for (size_t i = 1; i < preSum.size(); ++i) {
            preSum[i] = preSum[i - 1] + nums[i - 1];
        }
        for (size_t i = 1; i < preSum.size(); ++i) {
            if (preSum[i - 1] == preSum.back() - preSum[i])
                return i - 1;
        }
        return -1;
    }
};