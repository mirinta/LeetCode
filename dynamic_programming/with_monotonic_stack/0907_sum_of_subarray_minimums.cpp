#include <stack>
#include <vector>

/**
 * Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous)
 * subarray of arr. Since the answer may be large, return the answer modulo 10^9 + 7.
 *
 * ! 1 <= arr.length <= 3 * 10^4
 * ! 1 <= arr[i] <= 3 * 10^4
 */

class Solution
{
public:
    int sumSubarrayMins(std::vector<int>& arr)
    {
        constexpr int kMod = 1e9 + 7;
        // dp[i] = sum of min elements of all subarrays ending at arr[i]
        const int n = arr.size();
        const auto prevSmaller = getPreviousSmaller(arr);
        std::vector<long long> dp(n, 0);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            if (prevSmaller[i] == -1) {
                // case 1: arr[i] is the min element of arr[0:i]
                // {} <= arr[i], min = arr[i]
                // arr[i-1:i-1] <= arr[i], min = arr[i]
                // arr[i-2:i-1] <= arr[i], min = arr[i]
                // ...
                // arr[0:i-1] <= arr[i], min = arr[i]
                // thus, there are i+1 subarrays ending at arr[i] and arr[i] is the min element
                dp[i] = static_cast<long long>(i + 1) * arr[i];
            } else {
                // case 2: arr[i] is the min element of arr[j+1:i]
                const int j = prevSmaller[i];
                // {} <= arr[i], min = arr[i]
                // arr[i-1:i-1] <= arr[i], min = arr[i]
                // arr[i-2:i-1] <= arr[i], min = arr[i]
                // ...
                // arr[j+1:i-1] <= arr[i], min = arr[i]
                // there are i-j subarrays ending at arr[i] and arr[i] is the min element
                // ----
                // arr[j:i-1] <= arr[i], min = min[j:j]
                // arr[j-1:i-1] <= arr[i], min = min[j-1:j]
                // ...
                // arr[0:i-1] <= arr[i], min = min[0:j]
                // we know that min[j:j] + min[j-1:j] + ... + min[0:j] = dp[j]
                dp[i] = static_cast<long long>(i - j) * arr[i] + dp[j];
            }
            result = (result + dp[i]) % kMod;
        }
        return result;
    }

private:
    // prevSmaller[i] = largest j such that nums[j] < nums[i]
    std::vector<int> getPreviousSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> prevSmaller(n, -1);
        std::stack<int> stack;
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] <= nums[stack.top()]) {
                stack.pop();
            }
            prevSmaller[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return prevSmaller;
    }
};