#include <queue>
#include <set>
#include <vector>

/**
 * Given an array of integers nums and an integer limit, return the size of the longest non-empty
 * subarray such that the absolute difference between any two elements of this subarray is less than
 * or equal to limit.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 0 <= limit <= 10^9
 */

class Solution
{
public:
    int longestSubarray(std::vector<int>& nums, int limit) { return approach2(nums, limit); }

private:
    // sliding window + monotonic queue, time O(N), space O(N)
    int approach2(const std::vector<int>& nums, int limit)
    {
        std::deque<int> minDeque; // front is the min element
        std::deque<int> maxDeque; // front is the max element
        int result = 0;
        for (int left = 0, right = 0; right < nums.size(); ++right) {
            while (!minDeque.empty() && nums[right] < minDeque.back()) {
                minDeque.pop_back();
            }
            minDeque.push_back(nums[right]);
            while (!maxDeque.empty() && nums[right] > maxDeque.back()) {
                maxDeque.pop_back();
            }
            maxDeque.push_back(nums[right]);
            while (!maxDeque.empty() && !minDeque.empty() &&
                   maxDeque.front() - minDeque.front() > limit) {
                if (nums[left] == maxDeque.front()) {
                    maxDeque.pop_front();
                }
                if (nums[left] == minDeque.front()) {
                    minDeque.pop_front();
                }
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }

    // sliding window + multiset, time O(NlogN), space O(N)
    int approach1(const std::vector<int>& nums, int limit)
    {
        std::multiset<int> set;
        int result = 0;
        for (int left = 0, right = 0; right < nums.size(); ++right) {
            set.insert(nums[right]);
            while (*set.rbegin() - *set.begin() > limit) {
                set.erase(set.find(nums[left]));
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};
