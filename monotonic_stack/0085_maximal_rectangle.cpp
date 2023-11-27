#include <stack>
#include <vector>

/**
 * Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing
 * only 1's and return its area.
 *
 * ! rows == matrix.length
 * ! cols == matrix[i].length
 * ! 1 <= row, cols <= 200
 * ! matrix[i][j] is '0' or '1'.
 */

class Solution
{
public:
    int maximalRectangle(std::vector<std::vector<char>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::vector<int> info(n, 0); // info[j] = num of consecutive ones in the jth column
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == '1') {
                    info[j] += 1;
                } else {
                    info[j] = 0;
                }
            }
            const auto prevSmaller = genPrevSmaller(info);
            const auto nextSmaller = genNextSmaller(info);
            for (int j = 0; j < n; ++j) {
                result = std::max(result, info[j] * (nextSmaller[j] - (prevSmaller[j] + 1)));
            }
        }
        return result;
    }

private:
    std::vector<int> genPrevSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n);
        std::stack<int> stack;
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] <= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }

    std::vector<int> genNextSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n);
        std::stack<int> stack;
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] <= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return result;
    }
};