#include <vector>

/**
 Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Given the "root" of a binary tree and an integer "targetSum", return all root-to-leaf paths where
 * the sum of the node values in the path equals "targetSum". Each path should be returned as a list
 * of the node values, not node references.
 *
 * A root-to-leaf path is a path starting from the root and ending at any leaf node. A leaf node is
 * a node with no children.
 */

class Solution
{
public:
    std::vector<std::vector<int>> pathSum(TreeNode* root, int targetSum)
    {
        if (!root)
            return {};

        result.clear();
        std::vector<int> values;
        traverse(root, targetSum, values);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void traverse(TreeNode* node, int targetSum, std::vector<int>& values)
    {
        if (!node)
            return;

        if (targetSum == node->val && !node->left && !node->right) {
            result.push_back(values);
            result.back().push_back(node->val);
            return;
        }
        values.push_back(node->val);
        traverse(node->left, targetSum - node->val, values);
        traverse(node->right, targetSum - node->val, values);
        values.pop_back(); // process finished, pop the current value
    }
};
