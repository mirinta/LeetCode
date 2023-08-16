#include <queue>
#include <vector>

/**
 * Given an integer array "nums" and an integer "k", return the "k"th largest element in the array.
 *
 * Note that it is the "k"th largest element in the sorted order, not the "k"th distinct element.
 *
 * Can you solve it without sorting?
 *
 * ! 1 <= k <= nums.length <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 */

class Solution
{
public:
    int findKthLargest(std::vector<int>& nums, int k) { return approach2(nums, k); }

private:
    // Min Heap, time O(NlogK), space O(K)
    int approach1(const std::vector<int>& nums, int k)
    {
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq; // min heap
        for (const auto& val : nums) {
            pq.push(val);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        return pq.top();
    }

    // Quick-Select, time average O(N), time worst O(N^2), space O(1)
    int approach2(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        const int rank = n - k;
        int lo = 0;
        int hi = n - 1;
        while (lo < hi) {
            const int j = partition(nums, lo, hi);
            if (j == rank)
                return nums[j];

            if (j > rank) {
                hi = j - 1;
            } else {
                lo = j + 1;
            }
        }
        return nums[rank];
    }

    int partition(std::vector<int>& nums, int lo, int hi)
    {
        const int pivot = nums[lo];
        int i = lo + 1;
        int j = hi;
        while (true) {
            while (i <= hi && nums[i] <= pivot) {
                i++;
            }
            while (j >= lo && nums[j] > pivot) {
                j--;
            }
            if (i >= j)
                break;

            std::swap(nums[i], nums[j]);
        }
        std::swap(nums[lo], nums[j]);
        return j;
    }
};
