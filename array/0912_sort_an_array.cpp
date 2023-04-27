#include <vector>

/**
 * Given an array of integers "nums", sort the array in ascending order and return it.
 *
 * You must solve the problem without using any built-in functions in O(nlogn) time complexity and
 * with the smallest space complexity possible.
 */

class Solution
{
public:
    std::vector<int> sortArray(const std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        std::vector<int> result(nums);
        std::vector<int> auxiliary(nums.size(), 0);
        mergeSort(result, auxiliary, 0, result.size() - 1);
        return result;
    }

private:
    void mergeSort(std::vector<int>& result, std::vector<int>& auxiliary, int low, int high)
    {
        if (low >= high)
            return;

        const int mid = low + (high - low) / 2;
        mergeSort(result, auxiliary, low, mid);
        mergeSort(result, auxiliary, mid + 1, high);
        merge(result, auxiliary, low, mid, high);
    }

    // merge two sorted sub-arrays, [low, mid] and [mid + 1, high]
    void merge(std::vector<int>& result, std::vector<int>& auxiliary, int low, int mid, int high)
    {
        for (int i = low; i <= high; ++i) {
            auxiliary[i] = result[i];
        }
        for (int i = low, j = mid + 1, k = low; k <= high; ++k) {
            if (i > mid) {
                result[k] = auxiliary[j++];
                continue;
            }
            if (j > high) {
                result[k] = auxiliary[i++];
                continue;
            }
            if (auxiliary[i] > auxiliary[j]) {
                result[k] = auxiliary[j++];
            } else {
                result[k] = auxiliary[i++];
            }
        }
    }
};