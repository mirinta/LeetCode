#include <random>
#include <vector>

/**
 * Given an array of integers "nums", sort the array in ascending order and return it.
 *
 * You must solve the problem without using any built-in functions in O(nlogn) time complexity and
 * with the smallest space complexity possible.
 */

class Solution
{
    // approach 1: quick sort
public:
    std::vector<int> sortArray(const std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        std::vector<int> result(nums);
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(result.begin(), result.end(), g);
        quickSort3Way(result, 0, result.size() - 1);
        return result;
    }

private:
    void quickSort(std::vector<int>& nums, int low, int high)
    {
        if (low >= high)
            return;

        int pos = partition(nums, low, high);
        quickSort(nums, low, pos - 1);
        quickSort(nums, pos + 1, high);
    }

    int partition(std::vector<int>& nums, int low, int high)
    {
        int pivot = nums[low];
        // split [i, j] to [i, x - 1] and [x + 1, high] such that
        // - elements in [i, x - 1] <= pivot, and
        // - elements in [x + 1, high] > pivot;
        int i = low + 1;
        int j = high;
        while (true) {
            while (i <= high && nums[i] <= pivot) {
                i++;
            }
            while (j >= low && nums[j] > pivot) {
                j--;
            }
            if (i >= j)
                break;

            std::swap(nums[i], nums[j]);
        }
        std::swap(nums[low], nums[j]);
        return j;
    }

    void quickSort3Way(std::vector<int>& nums, int low, int high)
    {
        if (low >= high)
            return;

        // [low, lt - 1] < pivot
        // [lt, gt] == pivot
        // [gt + 1, high] > pivot
        int pivot = nums[low];
        int lt = low;
        int gt = high;
        int i = low + 1;
        while (i <= gt) {
            if (nums[i] < pivot) {
                std::swap(nums[i++], nums[lt++]);
            } else if (nums[i] > pivot) {
                std::swap(nums[i], nums[gt--]);
            } else {
                i++;
            }
        }
        quickSort3Way(nums, low, lt - 1);
        quickSort3Way(nums, gt + 1, high);
    }
    // ------------------------------
    // approach 2: merge sort
    // public:
    //     std::vector<int> sortArray(const std::vector<int>& nums)
    //     {
    //         if (nums.empty())
    //             return {};

    //         std::vector<int> result(nums);
    //         std::vector<int> auxiliary(nums.size(), 0);
    //         mergeSort(result, auxiliary, 0, result.size() - 1);
    //         return result;
    //     }

    // private:
    //     void mergeSort(std::vector<int>& result, std::vector<int>& auxiliary, int low, int high)
    //     {
    //         if (low >= high)
    //             return;

    //         const int mid = low + (high - low) / 2;
    //         mergeSort(result, auxiliary, low, mid);
    //         mergeSort(result, auxiliary, mid + 1, high);
    //         merge(result, auxiliary, low, mid, high);
    //     }

    //     // merge two sorted sub-arrays, [low, mid] and [mid + 1, high]
    //     void merge(std::vector<int>& result, std::vector<int>& auxiliary, int low, int mid, int
    //     high)
    //     {
    //         for (int i = low; i <= high; ++i) {
    //             auxiliary[i] = result[i];
    //         }
    //         for (int i = low, j = mid + 1, k = low; k <= high; ++k) {
    //             if (i > mid) {
    //                 result[k] = auxiliary[j++];
    //                 continue;
    //             }
    //             if (j > high) {
    //                 result[k] = auxiliary[i++];
    //                 continue;
    //             }
    //             if (auxiliary[i] > auxiliary[j]) {
    //                 result[k] = auxiliary[j++];
    //             } else {
    //                 result[k] = auxiliary[i++];
    //             }
    //         }
    //     }
};