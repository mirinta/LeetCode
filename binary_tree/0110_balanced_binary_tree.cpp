#include <utility>

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
 * Given a binary tree, determine if it is height-balanced.
 *
 * A height-balanced binary tree is a binary tree in which the depth of the subtrees of every node
 * never differs by more than one.
 */

class Solution
{
public:
    bool isBalanced(TreeNode* root)
    {
        if (!root)
            return true;

        return check(root) != -1;
    }

private:
    int check(TreeNode* node)
    {
        if (!node)
            return 0;

        // -1 means the tree is not balanced
        // if one of the subtrees is not balanced,
        // we no longer need to calculate the height
        const auto left = check(node->left);
        if (left == -1)
            return -1;

        const auto right = check(node->right);
        if (right == -1)
            return -1;

        return std::abs(left - right) > 1 ? -1 : 1 + std::max(left, right);
    }
};
