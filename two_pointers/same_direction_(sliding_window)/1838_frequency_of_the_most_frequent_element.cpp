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
        long long count = 0;
        int result = 1; // frequency >= 1
        for (int i = 1, j = 0; i < n; ++i) {
            // X X j X X X i-1 i
            //     |<------->|
            // nums[j:i-1] is already increased to nums[i-1]
            // increase nums[j:i-1] to nums[i]
            count += (i - j) * static_cast<long long>(nums[i] - nums[i - 1]);
            while (count > k) {
                count -= nums[i] - nums[j];
                j++;
            }
            result = std::max(result, i - j + 1);
        }
        return result;
    }
};