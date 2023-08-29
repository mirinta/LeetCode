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
 * Given the "root" of a binary tree, return its maximum depth.
 *
 * A binary tree's maximum depth is the number of nodes along the longest path from the root node
 * down to the farthest leaf node.
 *
 * ! The number of nodes in the tree is in the range [0, 10^4].
 * ! -100 <= Node.val <= 100
 */

class Solution
{
public:
    int maxDepth(TreeNode* root)
    {
        if (!root)
            return 0;

        const int left = maxDepth(root->left);
        const int right = maxDepth(root->right);
        return 1 + std::max(left, right);
    }
};
