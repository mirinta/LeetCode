#include <vector>

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
 * Given the "root" of a binary tree, determine if it is a valid binary search tree.
 *
 * A valid BST is defined as follows:
 *
 * - The left subtree of a node contains only nodes with keys less than the node's key.
 *
 * - The right subtree of a node contains only nodes with keys greater than the node's key.
 *
 * - Both the left and right subtrees must also be binary search trees.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -2^31 <= Node.val <= 2^31 - 1
 */

class Solution
{
public:
    bool isValidBST(TreeNode* root)
    {
        // return approach1(root, LONG_MIN, LONG_MAX);
        // return approach2(root);
        return approach3(root).first != LONG_MIN;
    }

private:
    // post-order traversal
    std::pair<long, long> approach3(TreeNode* root)
    {
        if (!root)
            return {LONG_MAX, LONG_MIN}; // make the following condition return true

        auto [leftMin, leftMax] = approach3(root->left);
        auto [rightMin, rightMax] = approach3(root->right);
        // a valid BST: leftMax < root.val < rightMin
        if (leftMax >= root->val || root->val >= rightMin)
            return {LONG_MIN, LONG_MAX}; // this makes the condition return false

        // we want {leftMin, rightMax}, but leftMin may be INT_MAX, and rightMax may be INT_MIN
        return {std::min<long>(root->val, leftMin), std::max<long>(root->val, rightMax)};
    }

    // pre-order traversal
    bool approach1(TreeNode* root, long min, long max)
    {
        if (!root)
            return true;

        if (root->val <= min || root->val >= max)
            return false;

        return approach1(root->left, min, root->val) && approach1(root->right, root->val, max);
    }

    // in-order traversal
    long prev{LONG_MIN};
    bool approach2(TreeNode* root)
    {
        if (!root)
            return true;

        if (!approach2(root->left))
            return false;

        if (root->val <= prev)
            return false;

        prev = root->val;
        return approach2(root->right);
    }
};