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
 * Given the "root" of a binary tree, invert the tree, and return its root.
 *
 * ! The number of nodes in the tree is in the range [0, 100].
 * ! -100 <= Node.val <= 100
 */

class Solution
{
public:
    TreeNode* invertTree(TreeNode* root)
    {
        if (!root)
            return nullptr;

        auto* left = invertTree(root->left);
        auto* right = invertTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
};