#include <stack>

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
 * Given the "root" of a binary search tree, and an integer "k", return the "k"th smallest value
 * (1-indexed) of all the values of the nodes in the tree.
 *
 * ! The number of nodes in the tree is "n".
 * ! 1 <= k <= n
 * ! 0 <= Node.val <= 10^4
 */

class Solution
{
public:
    int kthSmallest(TreeNode* root, int k)
    {
        // the in-order traversal of a BST gives nodes in ascending order
        return approach2(root, k);
    }

private:
    // Recursion
    int approach2(TreeNode* root, int k)
    {
        int result = -1;
        traverse(result, k, root);
        return result;
    }

    void traverse(int& result, int& k, TreeNode* node)
    {
        if (!node)
            return;

        traverse(result, k, node->left);
        if (result != -1)
            return;

        if (--k == 0) {
            result = node->val;
            return;
        }
        traverse(result, k, node->right);
    }

    // Iteration
    int approach1(TreeNode* root, int k)
    {
        if (!root)
            return -1;

        std::stack<TreeNode*> stack;
        auto* node = root;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            auto* top = stack.top();
            stack.pop();
            if (--k == 0)
                return top->val;

            node = top->right;
        }
        return -1;
    }
};
