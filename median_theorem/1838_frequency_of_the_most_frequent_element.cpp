#include <algorithm>
#include <vector>

/**
 * The frequency of an element is the number of times it occurs in an array.
 *
 * You are given an integer array nums and an integer k. In one operation, you can choose an index
 * of nums and increment the element at that index by 1.
 *
 * Return the maximum possible frequency of an element after performing at most k operations.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 * ! 1 <= k <= 10^5
 */

class Solution
{
public:
    int maxFrequency(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        // find a subarray nums[i:j] and increase nums[i:j-1] to nums[j]
        // check #operations <= k
        // let x = nums[j]
        // #operations = (x-nums[i]) + ... + (x-nums[j]) = (j-i+1)x - (nums[i] + ... + nums[j])
        int result = 0;
        long long sum = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            sum += nums[right];
            while (static_cast<long long>(right - left + 1) * nums[right] - sum > k) {
                sum -= nums[left];
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};