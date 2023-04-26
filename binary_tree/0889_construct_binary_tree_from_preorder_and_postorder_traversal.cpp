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
 * Given two integer arrays, "preorder" and "postorder" where "preorder" is the preorder traversal
 * of a binary tree of distinct values and "postorder" is the postorder traversal of the same tree,
 * reconstruct and return the binary tree.
 *
 * If there exist multiple answers, you can return any of them.
 *
 * ! All the values of "postorder" are unique.
 */