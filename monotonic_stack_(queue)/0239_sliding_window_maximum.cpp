#include <deque>
#include <vector>

/**
 * You are given an array of integers "nums", there is a sliding window of size "k" which is moving
 * from the very left of the array to the very right. You can only see the "k" numbers in the
 * window. Each time the sliding window moves right by one position.
 *
 * Return the max sliding window.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 * ! 1 <= k <= nums.length
 */

class Solution
{
public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::deque<int> deque; // monotonic queue, store index
        for (int i = 0; i < k; ++i) {
            addToDeque(deque, i, nums);
        }
        if (deque.empty())
            return {};

        std::vector<int> result{nums[deque.front()]};
        for (int i = k; i < n; ++i) {
            if (deque.front() == i - k) {
                deque.pop_front();
            }
            addToDeque(deque, i, nums);
            result.push_back(nums[deque.front()]);
        }
        return result;
    }

private:
    void addToDeque(std::deque<int>& deque, int index, const std::vector<int>& nums)
    {
        while (!deque.empty() && nums[index] >= nums[deque.back()]) {
            deque.pop_back();
        }
        deque.push_back(index);
    }
};
