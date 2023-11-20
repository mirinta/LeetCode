#include <stack>
#include <vector>

/**
 * You are given a 0-indexed array heights of positive integers, where heights[i] represents the
 * height of the ith building.
 *
 * If a person is in building i, they can move to any other building j if and only if i < j and
 * heights[i] < heights[j].
 *
 * You are also given another array queries where queries[i] = [ai, bi]. On the ith query, Alice is
 * in building ai while Bob is in building bi.
 *
 * Return an array ans where ans[i] is the index of the leftmost building where Alice and Bob can
 * meet on the ith query. If Alice and Bob cannot move to a common building on query i, set ans[i]
 * to -1.
 *
 * ! 1 <= heights.length <= 5 * 10^4
 * ! 1 <= heights[i] <= 10^9
 * ! 1 <= queries.length <= 5 * 10^4
 * ! queries[i] = [ai, bi]
 * ! 0 <= ai, bi <= heights.length - 1
 */

class Solution
{
public:
    std::vector<int> leftmostBuildingQueries(std::vector<int>& heights,
                                             std::vector<std::vector<int>>& queries)
    {
        const int n = heights.size();
        const auto nextGreater = genNextGreater(heights);
        std::vector<int> result(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            const int left = std::min(queries[i][0], queries[i][1]);
            int right = std::max(queries[i][0], queries[i][1]);
            if (right == left) {
                result[i] = left;
            } else if (heights[right] > heights[left]) {
                result[i] = right;
            } else if (nextGreater[left] == n) {
                result[i] = -1;
            } else {
                while (nextGreater[right] < n && heights[nextGreater[right]] <= heights[left]) {
                    right = nextGreater[right];
                }
                result[i] = nextGreater[right] == n ? -1 : nextGreater[right];
            }
        }
        return result;
    }

private:
    std::vector<int> genNextGreater(const std::vector<int>& heights)
    {
        // nextGreater[i] = j means heights[j] is the next greater element of heights[i]
        const int n = heights.size();
        std::vector<int> nextGreater(n);
        std::stack<int> stack;
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && heights[i] >= heights[stack.top()]) {
                stack.pop();
            }
            nextGreater[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return nextGreater;
    }
};