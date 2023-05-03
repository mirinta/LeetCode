#include <queue>

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
 * Given the "root" of a binary tree, return the leftmost value in the last row of the tree.
 */

class Solution
{
    int findBottomLeftValue(TreeNode* root)
    {
        if (!root)
            return -1;

        std::queue<TreeNode*> queue;
        queue.push(root);
        int result = -1;
        while (!queue.empty()) {
            auto* node = queue.front();
            queue.pop();
            result = node->val;
            // add right node first, then add left node
            // to make sure the leftmost node of each level is at the end of the queue
            if (node->right) {
                queue.push(node->right);
            }
            if (node->left) {
                queue.push(node->left);
            }
        }
        return result;
    }
};