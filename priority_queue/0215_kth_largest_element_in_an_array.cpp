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
    int findKthLargest(std::vector<int>& nums, int k) { return approach2(nums, k); }

private:
    int approach2(std::vector<int>& nums, int k)
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(nums.begin(), nums.end(), g);
        const int n = nums.size();
        const int rank = n - k; // index of the kth largest element
        int lo = 0;
        int hi = n - 1;
        while (lo < hi) {
            const auto [lt, gt] = threeWayPartition(nums, lo, hi);
            if (rank < lt) {
                hi = lt - 1;
            } else if (rank > gt) {
                lo = gt + 1;
            } else {
                return nums[rank];
            }
        }
        return nums[rank];
    }

    std::pair<int, int> threeWayPartition(std::vector<int>& nums, int lo, int hi)
    {
        // lo ... lt-1 lt ... gt gt+1 ... hi
        // |<-part1->| |<part2>| |<-part3->|
        // part1, nums[lo:lt-1] < pivot
        // part2, nums[lt:gt] = pivot
        // part3, nums[gt+1:hi] > pivot
        const int pivot = nums[lo];
        int lt = lo;
        int gt = hi;
        int i = lo;
        while (i <= gt) {
            if (nums[i] < pivot) {
                std::swap(nums[i++], nums[lt++]);
            } else if (nums[i] > pivot) {
                std::swap(nums[i], nums[gt--]);
            } else {
                i++;
            }
        }
        return {lt, gt};
    }

    int approach1(const std::vector<int>& nums, int k)
    {
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq; // min heap;
        for (const auto& val : nums) {
            pq.push(val);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        return pq.top();
    }
};
