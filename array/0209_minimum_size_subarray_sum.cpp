#include <vector>

/**
 * Given an array of positive integers "nums" and a positive integer "target", return the minimal
 * length of a sub-array whose sum is greater than or equal to "target". If there is no such
 * sub-array, return 0 instead.
 */

class Solution
{
public:
    int minSubArrayLen(int target, const std::vector<int>& nums)
    {
        if (nums.empty())
            return 0;

        int minLength = INT_MAX;
        int left = 0;
        int right = 0;
        int sum = 0;
        // sliding window, elements in range [left, right)
        while (right < nums.size()) {
            sum += nums[right++];
            while (sum >= target) {
                minLength = std::min(minLength, right - left);
                sum -= nums[left++];
            }
        }
        return minLength == INT_MAX ? 0 : minLength;
    }
};
