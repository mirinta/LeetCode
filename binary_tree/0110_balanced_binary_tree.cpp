#include <utility>

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
 * Given a binary tree, determine if it is height-balanced.
 *
 * A height-balanced binary tree is a binary tree in which the depth of the subtrees of every node
 * never differs by more than one.
 *
 * ! The number of nodes in the tree is in the range [0, 5000].
 * ! -10^4 <= Node.val <= 10^4
 */

class Solution
{
public:
    bool isBalanced(TreeNode* root) { return dfs(root) >= 0; }

private:
    // if the given binary tree is balanced, return its max depth
    // otherwise, return -1
    int dfs(TreeNode* root)
    {
        if (!root)
            return 0;

        const int leftMaxDepth = dfs(root->left);
        if (leftMaxDepth < 0)
            return -1;

        const int rightMaxDepth = dfs(root->right);
        if (rightMaxDepth < -1)
            return -1;

        if (std::abs(leftMaxDepth - rightMaxDepth) > 1)
            return -1;

        return 1 + std::max(leftMaxDepth, rightMaxDepth);
    }
};
