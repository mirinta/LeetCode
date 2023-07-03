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
        std::stack<std::pair<int, int>> stack;
        std::vector<int> result(temperatures.size(), 0);
        for (int i = temperatures.size() - 1; i >= 0; --i) {
            while (!stack.empty() && stack.top().first <= temperatures[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? 0 : stack.top().second - i;
            stack.push({temperatures[i], i});
        }
        return result;
    }
};