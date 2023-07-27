#include <stack>
#include <vector>

/**
 * Given an array of integers heights representing the histogram's bar height where the width of
 * each bar is 1, return the area of the largest rectangle in the histogram.
 *
 * ! 1 <= heights.length <= 10^5
 * ! 0 <= heights[i] <= 10^4
 */

class Solution
{
public:
    int largestRectangleArea(std::vector<int>& heights)
    {
        // for heights[i], we need to find j and k
        // - heights[j] is the previous smaller element of heights[i]
        // - heights[k] is the next smaller element of heights[i]
        // then, for each index p in range (j, k), heights[p] >= heights[i]
        // then, the rectangle area with heights[i] as height = heights[i] * (k - j - 1)
        const auto nextSmaller = genNextSmaller(heights);
        const auto prevSmaller = genPrevSmaller(heights);
        int result = 0;
        for (int i = 0; i < heights.size(); ++i) {
            result = std::max(result, heights[i] * (nextSmaller[i] - prevSmaller[i] - 1));
        }
        return result;
    }

private:
    std::vector<int> genNextSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n, n);
        std::stack<int> stack; // monotonic non-decreasing (from bottom to top)
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] < nums[stack.top()]) {
                result[stack.top()] = i;
                stack.pop();
            }
            stack.push(i);
        }
        return result;
    }

    std::vector<int> genPrevSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n, -1);
        std::stack<int> stack; // monotonic non-decreasing (from bottom to top)
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] < nums[stack.top()]) {
                stack.pop();
            }
            if (!stack.empty()) {
                result[i] = stack.top();
            }
            stack.push(i);
        }
        return result;
    }
};