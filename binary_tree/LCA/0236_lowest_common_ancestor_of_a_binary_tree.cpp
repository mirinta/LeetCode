/**
 * Definition for a binary tree node.
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
 *
 * ! The number of nodes in the tree is in the range [2, 10^5].
 * ! -10^9 <= Node.val <= 10^9
 * ! All Node.val are unique.
 * ! p != q
 * ! p and q will exist in the tree.
 */

class Solution
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        dfs(root, p->val, q->val);
        return result;
    }

private:
    TreeNode* result = nullptr;

    // count the number of values that the given "node" contains
    // NOTE, make sure val1 != val2
    int dfs(TreeNode* root, int val1, int val2)
    {
        if (!root)
            return 0;

        int count = root->val == val1 || root->val == val2 ? 1 : 0;
        count += dfs(root->left, val1, val2) + dfs(root->right, val1, val2);
        // the first node that contains both val1 and val2 is the answer
        if (count == 2 && !result) {
            result = root;
        }
        return count;
    }
};
