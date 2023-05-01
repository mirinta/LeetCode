/**
 Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 *
 * According to the definition of LCA on Wiki: The lowest common ancestor is defined between two
 * nodes "p" and "q" as the lowest node in "T" that has both "p" and "q" as descendants (where we
 * allow a node to be a descendant of itself).
 */

class Solution
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (!p || !q)
            return nullptr;

        return find(root, p->val, q->val);
    }

private:
    TreeNode* find(TreeNode* node, int val1, int val2)
    {
        if (!node)
            return nullptr;

        if (node->val == val1 || node->val == val2)
            return node;

        auto* left = find(node->left, val1, val2);
        auto* right = find(node->right, val1, val2);
        if (left && right)
            return node;

        return left ? left : right;
    }
};