#include <algorithm>
#include <vector>

/**
 * A swap is defined as taking two distinct positions in an array and swapping the values in them.
 *
 * A circular array is defined as an array where we consider the first element and the last element
 * to be adjacent.
 *
 * Given a binary circular array nums, return the minimum number of swaps required to group all 1's
 * present in the array together at any location.
 *
 * ! 1 <= nums.length <= 10^5
 * ! nums[i] is either 0 or 1.
 */

class Solution
{
public:
    int minSwaps(std::vector<int>& nums)
    {
        const int n = nums.size();
        const int zeros =
            std::count_if(nums.begin(), nums.end(), [](const auto& val) { return val == 0; });
        int ones = 0;
        int result = INT_MAX;
        for (int left = 0, right = 0; right < 2 * n; ++right) {
            ones += nums[right % n];
            if (right - left + 1 > zeros) {
                ones -= nums[left % n];
                left++;
            }
            if (right - left + 1 == zeros) {
                result = std::min(result, ones);
            }
        }
        return result;
    }
};