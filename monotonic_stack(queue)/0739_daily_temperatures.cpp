#include <stack>
#include <vector>

/**
 * Given an array of integers temperatures represents the daily temperatures, return an array answer
 * such that answer[i] is the number of days you have to wait after the ith day to get a warmer
 * temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.
 *
 * ! 1 <= temperatures.length <= 10^5
 * ! 30 <= temperatures[i] <= 100
 */

class Solution
{
public:
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures)
    {
        // given nums[i],
        // find the next greater element, i.e., nums[j] > nums[i]
        // then j-i is the num of days we have to wait after the ith day to get a warmer temperature
        const int n = temperatures.size();
        std::stack<std::pair<int, int>> stack; // <value, index>
        std::vector<int> result(n, 0);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && temperatures[i] >= stack.top().first) {
                stack.pop();
            }
            result[i] = stack.empty() ? 0 : stack.top().second - i;
            stack.emplace(temperatures[i], i);
        }
        return result;
    }
};
