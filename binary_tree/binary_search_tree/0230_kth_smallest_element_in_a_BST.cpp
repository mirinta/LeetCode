#include <stack>

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
 * ! 0 <= Node.val <= 10^4
 */

class Solution
{
public:
    int kthSmallest(TreeNode* root, int k) { return approach1(root, k); }

private:
    // iteration
    int approach2(TreeNode* root, int k)
    {
        std::stack<TreeNode*> stack;
        auto* node = root;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            node = stack.top();
            stack.pop();
            if (--k == 0)
                return node->val;

            node = node->right;
        }
        return -1;
    }

    // recursion
    int approach1(TreeNode* root, int k)
    {
        int result = -1;
        int count = 0;
        traverse(result, count, root, k);
        return result;
    }

    void traverse(int& result, int& count, TreeNode* node, int k)
    {
        if (!node)
            return;

        traverse(result, count, node->left, k);
        if (++count == k) {
            result = node->val;
            return;
        }
        traverse(result, count, node->right, k);
    }
};
