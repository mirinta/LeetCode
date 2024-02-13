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
        std::vector<int> result;
        result.reserve(n - k);
        std::deque<int> dq; // dq.front() is the index of the max element
        for (int i = 0; i < n; ++i) {
            if (!dq.empty() && dq.front() == i - k) {
                dq.pop_front();
            }
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
            if (i >= k - 1) {
                result.emplace_back(nums[dq.front()]);
            }
        }
        return result;
    }
};
