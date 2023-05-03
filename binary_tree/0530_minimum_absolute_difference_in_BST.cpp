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
 * Given the "root" of a BST, return the minimum absolute difference between the values of two
 * different nodes in the tree.
 *
 * ! This question is the same as 783.
 */

class Solution
{
public:
    int getMinimumDifference(TreeNode* root)
    {
        std::vector<int> inorder;
        traverse(root, inorder);
        if (inorder.empty())
            return -1;

        if (inorder.size() == 1)
            return inorder.front();

        int result = INT_MAX;
        for (size_t i = 1; i < inorder.size(); ++i) {
            result = std::min(result, inorder[i] - inorder[i - 1]);
        }
        return result;
    }

private:
    // the inorder traversal of a BST is sorted in ascending order
    void traverse(TreeNode* node, std::vector<int>& inorder)
    {
        if (!node)
            return;

        traverse(node->left, inorder);
        inorder.push_back(node->val);
        traverse(node->right, inorder);
    }
};