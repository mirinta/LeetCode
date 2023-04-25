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
 * Given the "root" of a binary tree, return the preorder traversal of its nodes' values.
 */

class Solution
{
public:
    std::vector<int> preorderTraversal(TreeNode* root)
    {
        std::vector<int> result;
        traverse(root, result);
        return result;
    }

private:
    void traverse(TreeNode* node, std::vector<int>& values)
    {
        if (!node)
            return;

        values.push_back(node->val);
        traverse(node->left, values);
        traverse(node->right, values);
    }
};