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
 * Given the "root" of a BST, convert it to a Greater Tree such that every key of the original BST
 * is changed to the original key plus all the sum of all keys greater than the original key in BST.
 *
 * As a reminder, a BST is a tree that satisfies these constraints:
 *
 * - The left subtree of a node contains only nodes with keys less than the node's key.
 *
 * - The right subtree of a node contains only nodes with keys greater than the node's key.
 *
 * - Both the left and right subtrees must also be BSTs.
 *
 * ! All the values in the tree are unique.
 *
 * ! "root" is guaranteed to be a valid BST.
 *
 * ! This question is the same as 538.
 */

class Solution
{
public:
    TreeNode* bstToGst(TreeNode* root)
    {
        if (!root)
            return nullptr;

        traverse(root);
        return root;
    }

private:
    int descendingOrderSum = 0;

    void traverse(TreeNode* node)
    {
        if (!node)
            return;

        traverse(node->right);
        descendingOrderSum += node->val;
        node->val = descendingOrderSum;
        traverse(node->left);
    }
};