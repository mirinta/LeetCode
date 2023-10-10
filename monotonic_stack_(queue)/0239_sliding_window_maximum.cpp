#include <cstddef>
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
        std::vector<int> result;
        std::deque<int> dq; // monotonic queue, non-increasing from front() to back()
        for (int i = 0; i < k; ++i) {
            addToDeque(dq, nums[i]);
        }
        result.push_back(dq.front());
        for (int i = k; i < nums.size(); ++i) {
            const auto& in = nums[i];
            const auto& out = nums[i - k];
            if (out == dq.front()) {
                dq.pop_front();
            }
            addToDeque(dq, in);
            result.push_back(dq.front());
        }
        return result;
    }

private:
    void addToDeque(std::deque<int>& dq, int val)
    {
        while (!dq.empty() && val > dq.back()) {
            dq.pop_back();
        }
        dq.push_back(val);
    }
};
