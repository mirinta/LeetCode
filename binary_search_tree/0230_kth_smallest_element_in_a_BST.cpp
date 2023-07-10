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
 * Given the "root" of a binary search tree, and an integer "k", return the "k"th smallest value
 * (1-indexed) of all the values of the nodes in the tree.
 *
 * ! The number of nodes in the tree is "n".
 * ! 1 <= k <= n
 */

class Solution
{
public:
    int kthSmallest(TreeNode* root, int k)
    {
        traverse(root, k);
        return result;
    }

private:
    int rank = 0;
    int result = 0;

    void traverse(TreeNode* node, int k)
    {
        if (!node)
            return;

        // BST: value of left node < node's value
        traverse(node->left, k);
        // here, we have the smallest value of the current subtree
        if (++rank == k) {
            result = node->val;
            return;
        }
        traverse(node->right, k);
    }
};