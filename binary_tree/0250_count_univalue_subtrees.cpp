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
 * Given the root of a binary tree, return the number of uni-value subtrees.
 *
 * A uni-value subtree means all nodes of the subtree have the same value.
 *
 * ! The number of the node in the tree will be in the range [0, 1000].
 * ! -1000 <= Node.val <= 1000
 */

class Solution
{
public:
    int countUnivalSubtrees(TreeNode* root)
    {
        int result = 0;
        traverse(result, root);
        return result;
    }

private:
    // return true if all values of the given tree are the same
    bool traverse(int& result, TreeNode* node)
    {
        if (!node)
            return true;

        const bool leftAllSame = traverse(result, node->left);
        const bool rightAllSame = traverse(result, node->right);
        if (!leftAllSame || !rightAllSame)
            return false;

        if ((!node->left || node->left->val == node->val) &&
            (!node->right || node->right->val == node->val)) {
            result++;
            return true;
        }
        return false;
    }
};