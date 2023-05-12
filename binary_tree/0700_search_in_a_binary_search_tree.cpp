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
 * You are given the "root" of a binary search tree and integer "val".
 *
 * Find the node in the BST that the node's value equals "val" and return the subtree rooted with
 * that node. If such a node does not exist, return nullptr.
 */

class Solution
{
public:
    // for the current root node of a BST:
    // root->left->val < root->val < root->right->val
    TreeNode* searchBST(TreeNode* root, int val)
    {
        // approach 1: recursion
        // if (!root)
        //     return nullptr;

        // if (root->val == val)
        //     return root;

        // return root->val > val ? searchBST(root->left, val) : searchBST(root->right, val);
        // approach 2: traverse
        if (!root)
            return nullptr;

        auto* node = root;
        while (node) {
            if (node->val == val)
                return node;

            node = node->val > val ? node->left : node->right;
        }
        return nullptr;
    }
};