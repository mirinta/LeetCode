#include <queue>
#include <random>
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
    int findKthLargest(std::vector<int>& nums, int k) { return approach1(nums, k); }

private:
    // priority-queue, time O(nlogk), space O(k)
    int approach2(std::vector<int>& nums, int k)
    {
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq; // min heap
        for (const auto& val : nums) {
            pq.push(val);
            while (pq.size() > k) {
                pq.pop();
            }
        }
        return pq.top();
    }

    // quick-select, worst time O(n^2), average time O(n), space O(1)
    int approach1(std::vector<int>& nums, int k)
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(nums.begin(), nums.end(), g);
        const int rank = nums.size() - k;
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo < hi) {
            const int pos = partition(lo, hi, nums);
            if (pos > rank) {
                hi = pos - 1;
            } else if (pos < rank) {
                lo = pos + 1;
            } else {
                return nums[pos];
            }
        }
        return -1;
    }

    int partition(int lo, int hi, std::vector<int>& nums)
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
        std::swap(nums[j], nums[lo]);
        return j;
    }
};
