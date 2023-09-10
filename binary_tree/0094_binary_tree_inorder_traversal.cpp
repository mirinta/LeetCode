#include <stack>
#include <vector>

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
 * Given the "root" of a binary tree, return the inorder traversal of its nodes' values.
 *
 * ! The number of nodes in the tree is in the range [0, 100].
 * ! -100 <= Node.val <= 100
 */

class Solution
{
public:
    std::vector<int> inorderTraversal(TreeNode* root) { return approach2(root); }

private:
    std::vector<int> approach2(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<int> result;
        std::stack<TreeNode*> stack;
        auto* node = root;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            auto* top = stack.top();
            stack.pop();
            result.push_back(top->val);
            node = top->right;
        }
        return result;
    }

    std::vector<int> approach1(TreeNode* root)
    {
        std::vector<int> result;
        traverse(result, root);
        return result;
    }

    void traverse(std::vector<int>& result, TreeNode* node)
    {
        if (!node)
            return;

        traverse(result, node->left);
        result.push_back(node->val);
        traverse(result, node->right);
    }
};