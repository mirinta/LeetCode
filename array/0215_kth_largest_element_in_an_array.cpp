#include <vector>

/**
 * Given an integer array "nums" and an integer "k", return the "k"th largest element in the array.
 *
 * Note that it is the "k"th largest element in the sorted order, not the "k"th distinct element.
 *
 * You must solve it in O(n) time complexity.
 */

class Solution
{
public:
    int findKthLargest(std::vector<int>& nums, int k)
    {
        if (nums.empty())
            return -1;

        int low = 0;
        int high = nums.size() - 1;
        // k is 1-indexed
        int rank = nums.size() - k; // 0-indexed, "rank + 1"th smallest = "k"th largest
        while (low <= high) {
            int pos = partition(nums, low, high);
            if (pos == rank)
                return nums[pos];

            if (pos > rank) {
                high = pos - 1;
            } else {
                low = pos + 1;
            }
        }
        return -1;
    }

private:
    int partition(std::vector<int>& nums, int low, int high)
    {
        int pivot = nums[low];
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
};