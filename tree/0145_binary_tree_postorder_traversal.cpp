#include <vector>

/**
 * Definition for a binary tree node.
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
 * Given the "root" of a binary tree, return the postorder traversal of its nodes' values.
 */

class Solution
{
public:
    std::vector<int> postorderTraversal(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<int> result;
        traverse(result, root);
        return result;
    }

private:
    void traverse(std::vector<int>& result, TreeNode* node)
    {
        if (!node)
            return;

        traverse(result, node->left);
        traverse(result, node->right);
        result.push_back(node->val);
    }
};