#include <stack>
#include <vector>

/**
 * We are given hours, a list of the number of hours worked per day for a given employee.
 *
 * A day is considered to be a tiring day if and only if the number of hours worked is (strictly)
 * greater than 8.
 *
 * A well-performing interval is an interval of days for which the number of tiring days is strictly
 * larger than the number of non-tiring days.
 *
 * Return the length of the longest well-performing interval.
 *
 * ! 1 <= hours.length <= 10^4
 * ! 0 <= hours[i] <= 16
 */

class Solution
{
public:
    int longestWPI(std::vector<int>& hours)
    {
        // let presum[i] = sum of nums[0:i-1]
        // - if nums[i] > 8, sum += 1
        // - if nums[i] <= 8, sum -= 1
        // if nums[j:i] is a valid interval,
        // then sum of nums[j:i] = presum[i+1] - presum[j] > 0
        // given presum[i], find the smallest j<i such that presum[i] > presum[j]
        // subarray length = i-1-j+1 = i-j, since j is the smallest, then length is maximized
        const int n = hours.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            const int val = hours[i - 1] > 8 ? 1 : -1;
            presum[i] = presum[i - 1] + val;
        }
        std::stack<int> stack; // monotonically decreasing (from bottom to top)
        for (int j = 0; j <= n; ++j) {
            if (stack.empty() || presum[stack.top()] > presum[j]) {
                stack.push(j);
            }
        }
        int result = 0;
        for (int i = n; i >= 0; --i) {
            while (!stack.empty() && presum[i] > presum[stack.top()]) {
                result = std::max(result, i - stack.top());
                stack.pop();
            }
        }
        return result;
    }
};