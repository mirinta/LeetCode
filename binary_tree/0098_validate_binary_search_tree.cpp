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
 */

class Solution
{
    // version 1:
    // public:
    //     bool isValidBST(TreeNode* root) {
    //         if (!root)
    //             return false;

    //         return traverse(root, nullptr, nullptr);
    //     }

    // private:
    //     bool traverse(TreeNode* node, TreeNode* minNode, TreeNode* maxNode)
    //     {
    //         if (!node)
    //             return true;
    //         // for the current root node, we want minNode < node < maxNode
    //         if (minNode && node->val <= minNode->val)
    //             return false;

    //         if (maxNode && node->val >= maxNode->val)
    //             return false;

    //         return traverse(node->left, minNode, node) && traverse(node->right, node, maxNode);
    //     }
    // version 2: if it is a valid BST, the inorder traversal is in ascending order.
public:
    bool isValidBST(TreeNode* root)
    {
        if (!root)
            return false;

        std::vector<int> inorder;
        traverse(root, inorder);
        for (size_t i = 0; inorder.size() > 1 && i < inorder.size() - 1; ++i) {
            if (inorder[i] >= inorder[i + 1])
                return false;
        }
        return true;
    }

private:
    void traverse(TreeNode* node, std::vector<int>& inorder)
    {
        if (!node)
            return;

        traverse(node->left, inorder);
        inorder.push_back(node->val);
        traverse(node->right, inorder);
    }
};