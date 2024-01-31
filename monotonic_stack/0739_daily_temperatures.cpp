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
        // find the next greater element of each temperatures[i]
        const int n = temperatures.size();
        std::stack<int> stack;
        std::vector<int> result(n, 0);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && temperatures[stack.top()] <= temperatures[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? 0 : stack.top() - i; // compute num of days
            stack.push(i);
        }
        return result;
    }
};
