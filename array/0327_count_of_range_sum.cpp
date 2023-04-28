#include <vector>

/**
 * Given an integer array "nums" and two integers "lower" and "upper", return the number of range
 * sums that lie in "[lower, upper]" inclusive.
 *
 * Range sum "S(i, j)" is defined as the sum of the elements in "nums" between indicies "i" and "j"
 * inclusive, where "i <= j".
 *
 * Example:
 * Input: nums = [-2, 5, -1], lower = -2, upper = 2
 * Output: 3
 * Explanation:
 * - range [0, 0], single number -2 is in [lower, upper]
 * - range [2, 2], single number -1 is in [lower, upper]
 * - range [0, 2], sum = -2 + 5 + -1 = 2 which is in [lower, upper]
 *
 * ! INT_MIN <= nums[i] <= INT_MAX, consider the overflow problem!
 */

/**
 * Let nums = [-2, 5, -1]
 * Then the prefix sum array is preSums = [0, -2, 3, 2]
 * During the process of merge sort, say merge [-2, 0] and [2, 3]
 * - pointer I iterates over [-2, 0] and pointer J iterates over [2, 3]
 * - given I, we need to count the number of J that satisfies lower <= val[J] - val[I] <= upper
 */
class Solution
{
public:
    int countRangeSum(std::vector<int>& nums, int lower, int upper)
    {
        if (nums.empty() || lower > upper)
            return 0;

        std::vector<long long> preSums(nums.size() + 1, 0); // put an extra value 0 at the front
        for (size_t i = 0; i < nums.size(); ++i) {
            preSums[i + 1] = nums[i] + preSums[i];
        }
        result = 0;
        lowerBound = lower;
        upperBound = upper;
        auxiliary.clear();
        auxiliary.resize(preSums.size(), 0);
        mergeSort(preSums, 0, preSums.size() - 1);
        return result;
    }

private:
    int result = 0;
    int lowerBound = 0;
    int upperBound = 0;
    std::vector<long long> auxiliary;

    void mergeSort(std::vector<long long>& nums, int low, int high)
    {
        if (low >= high)
            return;

        int mid = low + (high - low) / 2;
        mergeSort(nums, low, mid);
        mergeSort(nums, mid + 1, high);
        merge(nums, low, mid, high);
    }

    void merge(std::vector<long long>& nums, int low, int mid, int high)
    {
        // same as the standard merge sort
        for (size_t k = low; k <= high; ++k) {
            auxiliary[k] = nums[k];
        }
        // sliding window to count expected numbers, index range is [start, end)
        int start = mid + 1;
        int end = mid + 1;
        for (size_t i = low; i <= mid; ++i) {
            while (start <= high && nums[start] - nums[i] < lowerBound) {
                start++;
            }
            while (end <= high && nums[end] - nums[i] <= upperBound) {
                end++;
            }
            result += end - start;
        }
        // same as the standard merge sort
        for (size_t i = low, j = mid + 1, k = low; k <= high; ++k) {
            if (i > mid) {
                nums[k] = auxiliary[j++];
                continue;
            }
            if (j > high) {
                nums[k] = auxiliary[i++];
                continue;
            }
            if (auxiliary[i] > auxiliary[j]) {
                nums[k] = auxiliary[j++];
            } else {
                nums[k] = auxiliary[i++];
            }
        }
    }
};
