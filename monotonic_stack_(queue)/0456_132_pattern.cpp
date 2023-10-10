#include <stack>
#include <vector>

/**
 * Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i],
 * nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
 *
 * Return true if there is a 132 pattern in nums, otherwise, return false.
 *
 * ! n == nums.length
 * ! 1 <= n <= 2 * 10^5
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution
{
public:
    bool find132pattern(std::vector<int>& nums)
    {
        if (nums.size() < 3)
            return false;

        // 0 ... i ... j-1 j j+1 ... k ... n-1
        // |<---find i-->|   |<----find k--->|
        // given index j, and the min element on the left side of index j is nums[i] (i < j)
        // if nums[j] > nums[i],
        // then we need to find an index k > j such that nums[i] < nums[k] < nums[j]
        const int n = nums.size();
        // min element of nums[0],...,nums[i-1], it is in non-increasing order
        std::vector<int> min(n, INT_MAX);
        for (int i = 1; i < n; ++i) {
            min[i] = std::min(min[i - 1], nums[i - 1]);
        }
        std::stack<int> stack;
        for (int j = n - 1; j > 0; --j) {
            if (nums[j] <= min[j])
                continue;

            while (!stack.empty() && stack.top() <= min[j]) {
                stack.pop();
            }
            if (!stack.empty() && nums[j] > stack.top())
                return true;

            stack.push(nums[j]);
        }
        return false;
    }
};