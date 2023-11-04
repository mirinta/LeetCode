#include <deque>
#include <set>
#include <vector>

/**
 * You are given a 0-indexed integer array nums. A subarray of nums is called continuous if:
 *
 * Let i, i + 1, ..., j be the indices in the subarray. Then, for each pair of indices i <= i1, i2
 * <= j, 0 <= |nums[i1] - nums[i2]| <= 2. Return the total number of continuous subarrays.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution
{
public:
    long long continuousSubarrays(std::vector<int>& nums) { return approach2(nums); }

private:
    // sliding window + monotonic queue, O(N), space O(N)
    long long approach2(const std::vector<int>& nums)
    {
        long long result = 0;
        std::deque<int> min;
        std::deque<int> max;
        for (int left = 0, right = 0; right < nums.size(); ++right) {
            while (!min.empty() && nums[right] < min.back()) {
                min.pop_back();
            }
            min.push_back(nums[right]);
            while (!max.empty() && nums[right] > max.back()) {
                max.pop_back();
            }
            max.push_back(nums[right]);
            while (!min.empty() && !max.empty() && max.front() - min.front() > 2) {
                if (nums[left] == min.front()) {
                    min.pop_front();
                }
                if (nums[left] == max.front()) {
                    max.pop_front();
                }
                left++;
            }
            if (right >= left) {
                result += right - left + 1;
            }
        }
        return result;
    }

    // sliding window + multiset, time O(NlogN), space O(N)
    long long approach1(const std::vector<int>& nums)
    {
        long long result = 0;
        std::multiset<int> set;
        for (int left = 0, right = 0; right < nums.size(); ++right) {
            set.insert(nums[right]);
            while (!set.empty() && *set.rbegin() - *set.begin() > 2) {
                set.erase(set.find(nums[left++]));
            }
            result += set.size();
        }
        return result;
    }
};