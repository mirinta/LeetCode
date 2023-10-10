#include <stack>
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
    bool isValidBST(TreeNode* root) { return approach1(root); }

private:
    bool approach2(TreeNode* root)
    {
        if (!root)
            return false;

        return check(root, nullptr, nullptr);
    }

    bool check(TreeNode* root, TreeNode* min, TreeNode* max)
    {
        if (!root)
            return true;

        if (min && root->val <= min->val)
            return false;

        if (max && root->val >= max->val)
            return false;

        return check(root->left, min, root) && check(root->right, root, max);
    }

    bool approach1(TreeNode* root)
    {
        if (!root)
            return false;

        // inorder traversal of a BST gives nodes in ascending order
        auto* node = root;
        std::stack<TreeNode*> stack;
        std::vector<int> values;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            auto* top = stack.top();
            stack.pop();
            if (!values.empty() && top->val <= values.back())
                return false;

            values.push_back(top->val);
            node = top->right;
        }
        return true;
    }
};
