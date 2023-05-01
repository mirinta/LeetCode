#include <cstddef>
#include <deque>
#include <vector>

/**
 * You are given an array of integers "nums", there is a sliding window of size "k" which is moving
 * from the very left of the array to the very right. You can only see the "k" numbers in the
 * window. Each time the sliding window moves right by one position.
 *
 * Return the max sliding window.
 */

class Solution
{
public:
    std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k)
    {
        if (nums.empty() || nums.size() < k)
            return {};

        std::vector<int> result;
        // decreasing monotonic queue
        // front [x0, x1, ..., xn] back
        // we need to maintain x0 >= x1 >= ... >= xn
        std::deque<int> dq;
        for (size_t i = 0; i < k; ++i) {
            push(dq, nums[i]);
        }
        result.push_back(dq.front());
        for (size_t i = k; i < nums.size(); ++i) {
            if (nums[i - k] == dq.front()) {
                dq.pop_front();
            }
            push(dq, nums[i]);
            result.push_back(dq.front());
        }
        return result;
    }

private:
    void push(std::deque<int>& dq, int val)
    {
        while (!dq.empty() && dq.back() < val) {
            dq.pop_back();
        }
        dq.push_back(val);
    }
};