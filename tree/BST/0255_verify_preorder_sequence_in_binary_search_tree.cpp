#include <stack>
#include <vector>

/**
 * Given an array of unique integers preorder, return true if it is the correct preorder traversal
 * sequence of a binary search tree.
 *
 * ! 1 <= preorder.length <= 10^4
 * ! 1 <= preorder[i] <= 10^4
 * ! All the elements of preorder are unique.
 */

class Solution
{
public:
    bool verifyPreorder(std::vector<int>& preorder) { return approach2(preorder); }

private:
    bool approach2(const std::vector<int>& preorder)
    {
        int min = INT_MIN;
        std::stack<int> stack; // monotonic decreasing
        for (const auto& val : preorder) {
            while (!stack.empty() && stack.top() < val) {
                min = stack.top();
                stack.pop();
            }
            if (val <= min)
                return false;

            stack.push(val);
        }
        return true;
    }

    bool approach1(const std::vector<int>& preorder)
    {
        return dfs(preorder, 0, preorder.size() - 1);
    }

    bool dfs(const std::vector<int>& preorder, int start, int end)
    {
        if (start >= end)
            return true;

        // 5 2 1 3 6
        // - [5] is the root node
        // - [2 1 3] is the left subtree
        // - [6] is the right subtree
        // all values in the left subtree < root->val
        // all values in the right subtree > root->val
        const int rootValue = preorder[start];
        int rightChildIdx = start + 1;
        while (rightChildIdx <= end && preorder[rightChildIdx] < rootValue) {
            rightChildIdx++;
        }
        for (int i = rightChildIdx; i <= end; ++i) {
            if (preorder[i] <= rootValue)
                return false;
        }
        return dfs(preorder, start + 1, rightChildIdx - 1) && dfs(preorder, rightChildIdx, end);
    }
};
