#include <vector>

/**
 * Given an array of positive integers "nums" and a positive integer "target", return the minimal
 * length of a sub-array whose sum is greater than or equal to "target". If there is no such
 * sub-array, return 0 instead.
 *
 * ! 1 <= target <= 10^9
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^4
 */

class Solution
{
public:
    int minSubArrayLen(int target, std::vector<int>& nums) { return approach1(target, nums); }

private:
    // binary search, time O(NlogN), space O(N)
    int approach2(int target, const std::vector<int>& nums)
    {
        if (nums.empty())
            return 0;

        // prefix[j] = sum(nums[0]...nums[i]...nums[j])
        // prefix[i-1] = sum(nums[0]...nums[i-1])
        // if sum(nums[i]...nums[j]) >= target
        // then prefix[j] - prefix[i-1] >= target
        // prefix[i] is strictly increasing, because all elements are positive numbers
        const int n = nums.size();
        std::vector<int> prefix(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] + nums[i - 1];
        }
        int result = INT_MAX;
        for (int i = 1; i <= n; ++i) {
            auto iter = std::lower_bound(prefix.begin(), prefix.end(), prefix[i - 1] + target);
            if (iter != prefix.end()) {
                result = std::min<int>(result, std::distance(prefix.begin(), iter) - i + 1);
            }
        }
        return result == INT_MAX ? 0 : result;
    }

    // sliding window, time O(N), O(1)
    int approach1(int target, const std::vector<int>& nums)
    {
        if (nums.empty())
            return 0;

        // X X L X X X X R R+1
        //     |<--sum-->|
        int left = 0;
        int right = 0;
        int sum = 0;
        int result = INT_MAX;
        while (right < nums.size()) {
            sum += nums[right++];
            while (sum >= target) {
                result = std::min(result, right - left);
                sum -= nums[left++];
            }
        }
        return result == INT_MAX ? 0 : result;
    }
};
