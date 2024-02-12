#include <stack>
#include <vector>

/**
 * The min-product of an array is equal to the minimum value in the array multiplied by the array's
 * sum.
 *
 * For example, the array [3,2,5] (minimum value is 2) has a min-product of 2 * (3+2+5) = 2 * 10
 * = 20. Given an array of integers nums, return the maximum min-product of any non-empty subarray
 * of nums. Since the answer may be large, return it modulo 10^9 + 7.
 *
 * Note that the min-product should be maximized before performing the modulo operation. Testcases
 * are generated such that the maximum min-product without modulo will fit in a 64-bit signed
 * integer.
 *
 * A subarray is a contiguous part of an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^7
 */

class Solution
{
public:
    int maxSumMinProduct(std::vector<int>& nums)
    {
        // for each nums[i],
        // find the longest subarray nums[j:k] such that its min element is nums[i]
        // j = prevSmaller(nums[i]) + 1, the smallest index such that nums[j] >= nums[i]
        // k = nextSmaller(nums[i]) - 1, the largest index such that nums[k] >= nums[i]
        constexpr int kMod = 1e9 + 7;
        const int n = nums.size();
        std::vector<long long> presum(n + 1, 0); // presum[i] = nums[0]+...+nums[i-1]
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        const auto prevSmaller = getPrevSmaller(nums);
        const auto nextSmaller = getNextSmaller(nums);
        long long result = 0; // all nums[i] are positive integers
        for (int i = 0; i < n; ++i) {
            const int j = prevSmaller[i] + 1;
            const int k = nextSmaller[i] - 1;
            const auto score = (presum[k + 1] - presum[j]) * nums[i];
            result = std::max(result, score);
        }
        return result % kMod;
    }

private:
    std::vector<int> getPrevSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n);
        std::stack<int> stack;
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[stack.top()] >= nums[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }

    std::vector<int> getNextSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n);
        std::stack<int> stack;
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[stack.top()] >= nums[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return result;
    }
};