#include <algorithm>

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
 * Given the "root" of a binary tree, return the length of the diameter of the tree.
 *
 * The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
 * This path may or may not pass through the "root".
 *
 *
 * The length of a path between two nodes is represented by the number of edges between them.
 */

class Solution
{
public:
    int diameterOfBinaryTree(TreeNode* root)
    {
        maxDepth(root);
        return result;
    }

private:
    int result = 0;
    int maxDepth(TreeNode* node)
    {
        if (!node)
            return 0;

        int left = maxDepth(node->left);
        int right = maxDepth(node->right);
        // diameter = max depth of left subtree + max depth of right sub-tree
        result = std::max(result, left + right);
        return 1 + std::max(left, right);
    }
};
