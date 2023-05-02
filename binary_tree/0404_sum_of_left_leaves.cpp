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
 * Given the "root" of a binary tree, return the sum of all left leaves.
 *
 * A leaf if a node with no children. A left leaf is a leaf that is the left child of another node.
 */

class Solution
{
public:
    int sumOfLeftLeaves(TreeNode* root)
    {
        if (!root)
            return 0;

        int result = 0;
        traverse(root, result);
        return result;
    }

private:
    void traverse(TreeNode* node, int& result)
    {
        if (!node)
            return;

        auto* leftChild = node->left;
        // check the left child node is a leaf node:
        if (leftChild && !leftChild->left && !leftChild->right) {
            result += leftChild->val;
        }
        traverse(node->left, result);
        traverse(node->right, result);
    }
};