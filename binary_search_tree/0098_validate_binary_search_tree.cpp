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
 * Given the "root" of a binary tree, determine if it is a valid binary search tree.
 *
 * A valid BST is defined as follows:
 *
 * - The left subtree of a node contains only nodes with keys less than the node's key.
 *
 * - The right subtree of a node contains only nodes with keys greater than the node's key.
 *
 * - Both the left and right subtrees must also be binary search trees.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -2^31 <= Node.val <= 2^31 - 1
 */

class Solution
{
public:
    bool isValidBST(TreeNode* root) { return approach1(root); }

private:
    bool approach2(TreeNode* root)
    {
        if (!root)
            return false;

        return validate(root, nullptr, nullptr);
    }

    bool validate(TreeNode* current, TreeNode* min, TreeNode* max)
    {
        if (!current)
            return true;

        if (min && min->val >= current->val)
            return false;

        if (max && max->val <= current->val)
            return false;

        return validate(current->left, min, current) && validate(current->right, current, max);
    }

    bool approach1(TreeNode* root)
    {
        if (!root)
            return false;

        std::vector<int> inorder;
        traverse(inorder, root);
        for (int i = 1; i < inorder.size(); ++i) {
            if (inorder[i] <= inorder[i - 1])
                return false;
        }
        return true;
    }

    void traverse(std::vector<int>& inorder, TreeNode* node)
    {
        if (!node)
            return;

        traverse(inorder, node->left);
        inorder.push_back(node->val);
        traverse(inorder, node->right);
    }
};
