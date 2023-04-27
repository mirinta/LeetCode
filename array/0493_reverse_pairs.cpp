#include <vector>

/**
 * Given an integer array "nums", return the number of reverse pairs in the array.
 *
 * A reverse pair is a pair "(i, j)" where:
 *
 * - 0 <= i < j < nums.length, and
 *
 * - nums[i] > 2 * nums[j]
 */

class Solution
{
public:
    int reversePairs(std::vector<int>& nums)
    {
        if (nums.size() < 2)
            return 0;

        result = 0; // reset
        auxiliary.clear();
        auxiliary.resize(nums.size(), 0);
        mergeSort(nums, 0, nums.size() - 1);
        return result;
    }

private:
    int result;
    std::vector<int> auxiliary;

    void mergeSort(std::vector<int>& nums, int low, int high)
    {
        if (low >= high)
            return;

        int mid = low + (high - low) / 2;
        mergeSort(nums, low, mid);
        mergeSort(nums, mid + 1, high);
        merge(nums, low, mid, high);
    }

    void merge(std::vector<int>& nums, int low, int mid, int high)
    {
        // same as the standard merge sort
        for (size_t i = low; i <= high; ++i) {
            auxiliary[i] = nums[i];
        }
        // count the number of values that nums[i] > nums[j]
        // here, we have low <= i <= mid < j <= high,
        // the sub-arrays [low, mid] and [mid + 1, high] are sorted in ascending order
        int end = mid + 1;
        for (size_t i = low; i <= mid; ++i) {
            while (end <= high && nums[i] - 2 * static_cast<long long>(nums[end]) > 0) {
                end++;
            }
            result += end - mid - 1;
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